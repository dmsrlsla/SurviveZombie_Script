// Fill out your copyright notice in the Description page of Project Settings.


#include "SZWeapon_Inst.h"
#include "DrawDebugHelpers.h"
#include "SZImpactEffect.h"


ASZWeapon_Inst::ASZWeapon_Inst(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CurrentFiringSpread = 0.0f;
}

void ASZWeapon_Inst::FireWeapon()
{
	const int32 RandomSeed = FMath::Rand();
	FRandomStream WeaponRandomStream(RandomSeed);
	const float CurrentSpread = GetCurrentSpread();
	const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

	const FVector AimDir = GetWeaponAim();
	const FVector StartTrace = GetWeaponDamageStartLocation(AimDir);
	const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
	const FVector EndTrace = StartTrace + (ShootDir * InstantConfig.WeaponRange);
	
	const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);

	CurrentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, CurrentFiringSpread + InstantConfig.FiringSpreadIncrement);
	
	//DrawDebugLine(
	//	GetWorld(),
	//	StartTrace,
	//	EndTrace,
	//	FColor(255, 0, 0),
	//	false, 3, 0,
	//	1.f
	//);

	
	
	//UE_LOG(LogClass, Warning, TEXT("%f"), EndTrace);
}

bool ASZWeapon_Inst::ServerNotifyHit_Validate(const FHitResult& Impact, FVector_NetQuantizeNormal ShootDir, int32 RandomSeed, float ReticleSpread)
{
	return true;
}

void ASZWeapon_Inst::ServerNotifyHit_Implementation(const FHitResult& Impact, FVector_NetQuantizeNormal ShootDir, int32 RandomSeed, float ReticleSpread)
{
	const float WeaponAngleDot = FMath::Abs(FMath::Sin(ReticleSpread * PI / 180.f));
	
	if (Instigator && (Impact.GetActor() || Impact.bBlockingHit))
	{
		const FVector Origin = GetMuzzleLocation();
		const FVector ViewDir = (Impact.Location - Origin).GetSafeNormal();
	
		const float ViewDotHitDir = FVector::DotProduct(Instigator->GetViewRotation().Vector(), ViewDir);
		if (ViewDotHitDir > InstantConfig.AllowedViewDotHitDir - WeaponAngleDot)
		{
			if (CurrentState != EWeaponState::Idle)
			{
				if (Impact.GetActor() == NULL)
				{
					if (Impact.bBlockingHit)
					{
						ProcessInstantHit_Confirmed(Impact, Origin, ShootDir, RandomSeed, ReticleSpread);
					}
				}
				else if (Impact.GetActor()->IsRootComponentStatic() || Impact.GetActor()->IsRootComponentStationary())
				{
					ProcessInstantHit_Confirmed(Impact, Origin, ShootDir, RandomSeed, ReticleSpread);
				}
				else
				{
					// Get the component bounding box
					const FBox HitBox = Impact.GetActor()->GetComponentsBoundingBox();
	
					// calculate the box extent, and increase by a leeway
					FVector BoxExtent = 0.5 * (HitBox.Max - HitBox.Min);
					BoxExtent *= InstantConfig.ClientSideHitLeeway;
	
					// avoid precision errors with really thin objects
					BoxExtent.X = FMath::Max(20.0f, BoxExtent.X);
					BoxExtent.Y = FMath::Max(20.0f, BoxExtent.Y);
					BoxExtent.Z = FMath::Max(20.0f, BoxExtent.Z);
	
					// Get the box center
					const FVector BoxCenter = (HitBox.Min + HitBox.Max) * 0.5;
	
					// if we are within client tolerance
					if (FMath::Abs(Impact.Location.Z - BoxCenter.Z) < BoxExtent.Z &&
						FMath::Abs(Impact.Location.X - BoxCenter.X) < BoxExtent.X &&
						FMath::Abs(Impact.Location.Y - BoxCenter.Y) < BoxExtent.Y)
					{
						ProcessInstantHit_Confirmed(Impact, Origin, ShootDir, RandomSeed, ReticleSpread);
					}
				}
			}
		}
	}
}

bool ASZWeapon_Inst::ServerNotifyMiss_Validate(FVector_NetQuantizeNormal ShootDir, int32 RandomSeed, float ReticleSpread)
{
	return true;
}

void ASZWeapon_Inst::ServerNotifyMiss_Implementation(FVector_NetQuantizeNormal ShootDir, int32 RandomSeed, float ReticleSpread)
{
	const FVector Origin = GetMuzzleLocation();

	// play FX on remote clients
	HitNotify.Origin = Origin;
	HitNotify.RandomSeed = RandomSeed;
	HitNotify.ReticleSpread = ReticleSpread;


	// play FX locally
	if (GetNetMode() != NM_DedicatedServer)
	{
		const FVector EndTrace = Origin + ShootDir * InstantConfig.WeaponRange;
		SpawnTrailEffect(EndTrace);
	}
}

void ASZWeapon_Inst::ProcessInstantHit(const FHitResult & Impact, const FVector & Origin, const FVector & ShootDir, int32 RandomSeed, float ReticleSpread)
{
	if (MyPawn && MyPawn->IsLocallyControlled()&& GetNetMode() == NM_Client)
	{
		// if we're a client and we've hit something that is being controlled by the server
		if (Impact.GetActor() && Impact.GetActor()->GetRemoteRole() == ROLE_Authority)
		{
			// notify the server of the hit
			ServerNotifyHit(Impact, ShootDir, RandomSeed, ReticleSpread);
		}
		else if (Impact.GetActor() == NULL)
		{
			if (Impact.bBlockingHit)
			{
				// notify the server of the hit
				ServerNotifyHit(Impact, ShootDir, RandomSeed, ReticleSpread);
			}
			else
			{
				// notify server of the miss
				ServerNotifyMiss(ShootDir, RandomSeed, ReticleSpread);
			}
		}
	}

	// process a confirmed hit
	ProcessInstantHit_Confirmed(Impact, Origin, ShootDir, RandomSeed, ReticleSpread);
}

void ASZWeapon_Inst::ProcessInstantHit_Confirmed(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir, int32 RandomSeed, float ReticleSpread)
{
	if (ShouldDealDamage(Impact.GetActor()))
	{
		DealDamage(Impact, ShootDir);
	}

	// play FX on remote clients
	if (Role == ROLE_Authority)
	{
		HitNotify.Origin = Origin;
		HitNotify.RandomSeed = RandomSeed;
		HitNotify.ReticleSpread = ReticleSpread;
	}

	// play FX locally
	if (GetNetMode() != NM_DedicatedServer)
	{
		const FVector EndTrace = Origin + ShootDir * InstantConfig.WeaponRange;
		const FVector EndPoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;

		SpawnTrailEffect(EndPoint);
		SpawnImpactEffects(Impact);
	}
}

bool ASZWeapon_Inst::ShouldDealDamage(AActor * TestActor) const
{
	if (TestActor)
	{
		if (GetNetMode() != NM_Client ||
			TestActor->Role == ROLE_Authority ||
			TestActor->GetTearOff())
		{
			return true;
		}
	}

	return false;
}

void ASZWeapon_Inst::DealDamage(const FHitResult & Impact, const FVector & ShootDir)
{
	FPointDamageEvent PointDmg;
	//PointDmg.DamageTypeClass = FPointDamageEvent::ClassID
	PointDmg.HitInfo = Impact;
	PointDmg.ShotDirection = ShootDir;
	PointDmg.Damage = InstantConfig.HitDamage;

	Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, MyPawn->Controller, this);
}



void ASZWeapon_Inst::OnBurstFinished()
{
	Super::OnBurstFinished();

	CurrentFiringSpread = 0.0f;
}


//////////////////////////////////////////////////////////////////////////
// Weapon usage helpers

float ASZWeapon_Inst::GetCurrentSpread() const
{
	float FinalSpread = InstantConfig.WeaponSpread + CurrentFiringSpread;
	

	return FinalSpread;
}




//////////////////////////////////////////////////////////////////////////
// Replication & effects


void ASZWeapon_Inst::OnRep_HitNotify()
{
	SimulateInstantHit(HitNotify.Origin, HitNotify.RandomSeed, HitNotify.ReticleSpread);
}

void ASZWeapon_Inst::SimulateInstantHit(const FVector & ShotOrigin, int32 RandomSeed, float ReticleSpread)
{
	FRandomStream WeaponRandomStream(RandomSeed);
	const float ConeHalfAngle = FMath::DegreesToRadians(ReticleSpread * 0.5f);

	const FVector StartTrace = ShotOrigin;
	const FVector AimDir = GetWeaponAim();
	const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
	const FVector EndTrace = StartTrace + ShootDir * InstantConfig.WeaponRange;

	FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
	if (Impact.bBlockingHit)
	{
		SpawnImpactEffects(Impact);
		SpawnTrailEffect(Impact.ImpactPoint);
	}
	else
	{
		SpawnTrailEffect(EndTrace);
	}
}

void ASZWeapon_Inst::SpawnImpactEffects(const FHitResult & Impact)
{
	if (ImpactTemplate &&Impact.bBlockingHit)
	{
		FHitResult UseImpact = Impact;
	
		// trace again to find component lost during replication
		if (!Impact.Component.IsValid())
		{
			const FVector StartTrace = Impact.ImpactPoint + Impact.ImpactNormal * 10.0f;
			const FVector EndTrace = Impact.ImpactPoint - Impact.ImpactNormal * 10.0f;
			FHitResult Hit = WeaponTrace(StartTrace, EndTrace);
			UseImpact = Hit;
		}
	
		FTransform const SpawnTransform(Impact.ImpactNormal.Rotation(), Impact.ImpactPoint);
		ASZImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<ASZImpactEffect>(ImpactTemplate, SpawnTransform);
		if (EffectActor)
		{
			EffectActor->SurfaceHit = UseImpact;
			UGameplayStatics::FinishSpawningActor(EffectActor, SpawnTransform);
		}
	}
}

void ASZWeapon_Inst::SpawnTrailEffect(const FVector & EndPoint)
{
	if (TrailFX)
	{
		const FVector OriginLoc = GetMuzzleLocation();
		const FRotator OriginRot = GetMuzzleDirection().Rotation();
	
		//UParticleSystemComponent*TrailPSC = UGameplayStatics::SpawnEmitterAttached(TrailFX,RootComponent, MuzzleAttachPoint,OriginLoc,);
		UParticleSystemComponent* TrailPSC = UGameplayStatics::SpawnEmitterAttached( TrailFX,RootComponent,MuzzleAttachPoint, OriginLoc, OriginRot, EAttachLocation::KeepWorldPosition,true,EPSCPoolMethod::AutoRelease);
		if (TrailPSC)
		{
			TrailPSC->SetVectorParameter(TrailTargetParam, EndPoint);
			
		}
	}
}

void ASZWeapon_Inst::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASZWeapon_Inst, HitNotify, COND_SkipOwner);
}
