// Fill out your copyright notice in the Description page of Project Settings.


#include "SZClipBase.h"
#include "SZWeaponBase.h"

ASZClipBase::ASZClipBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FullBody = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FullBody"));
	FullBody->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	FullBody->bReceivesDecals = false;
	FullBody->CastShadow = true;
	RootComponent = FullBody;

	EmptyBody = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("EmptyBody"));
	EmptyBody->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	EmptyBody->bReceivesDecals = false;
	EmptyBody->CastShadow = true;
	EmptyBody->SetupAttachment(FullBody);
	EmptyBody->SetHiddenInGame(true);

	

	bAttachedWeapon = false;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;

	bAttachedHand = false;
}




void ASZClipBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ClipConfig.AmmoPerClip > 0)
	{
		CurrentAmmoInClip = ClipConfig.AmmoPerClip;
	}
}

void ASZClipBase::Destroyed()
{
	Super::Destroyed();

}

void ASZClipBase::AttachMeshToWeapon(ASZWeaponBase * Weapon)
{
	if (Weapon)
	{
		if (Weapon->IsA(WeaponType))
		{
			FName AttachPoint = Weapon->GetClipAttachPoint();
			USkeletalMeshComponent* UsePawnMesh = Weapon->GetWeaponMesh();
			FVector Origin, BoxSize;
			this->GetActorBounds(false, Origin, BoxSize);
			FullBody->AttachToComponent(UsePawnMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
			FullBody->SetRelativeLocation(FVector(0.f, 0.f, -BoxSize.Z * 0.5f));
			
			EmptyBody->AttachToComponent(UsePawnMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachPoint);
			EmptyBody->SetRelativeLocation(FVector(0.f, 0.f, -BoxSize.Z * 0.5f));
			bAttachedWeapon = true;
		}
	}
}

void ASZClipBase::DetachMeshFromWeapon()
{
	FullBody->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	EmptyBody->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	bAttachedWeapon = false;
	
	FullBody->SetSimulatePhysics(true);
	EmptyBody->SetSimulatePhysics(true);
	if (GetCurrentAmmoInClip() == 0)
	{
		FullBody->SetHiddenInGame(true);
		EmptyBody->SetHiddenInGame(false);
		Destroy(true);
	}
	else
	{
		FullBody->SetHiddenInGame(false);
		EmptyBody->SetHiddenInGame(true);
	}

	
}


bool ASZClipBase::IsAttachedToWeapon() const
{
	return bAttachedWeapon;
}

USkeletalMeshComponent * ASZClipBase::GetFullMesh()
{
	return FullBody;
}

void ASZClipBase::UseAmmo()
{
	if (!HasInfiniteClip())
	{
		CurrentAmmoInClip--;
	}


	if (GetCurrentAmmoInClip() == 0)
	{
		DetachMeshFromWeapon();
	}
}

//int32 ASZClipBase::GetCurrentAmmo() const
//{
//	return CurrentAmmo;
//}

int32 ASZClipBase::GetCurrentAmmoInClip() const
{
	return CurrentAmmoInClip;
}


bool ASZClipBase::HasInfiniteClip() const
{
	return ClipConfig.bInfiniteClip;
}


void ASZClipBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASZClipBase, CurrentAmmoInClip, COND_OwnerOnly);
}


