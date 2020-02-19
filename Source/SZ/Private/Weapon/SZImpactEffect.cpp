// Fill out your copyright notice in the Description page of Project Settings.


#include "SZImpactEffect.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"

ASZImpactEffect::ASZImpactEffect(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bAutoDestroyWhenFinished = true;
}

void ASZImpactEffect::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UPhysicalMaterial* HitPhysMat = SurfaceHit.PhysMaterial.Get();
	EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitPhysMat);

	//show Particles
	UParticleSystem * ImpactFX = GetImpactFX(HitSurfaceType);
	if (ImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
	}

	//play Sound
	USoundBase * ImpactSound = GetImpactSound(HitSurfaceType);
	if (ImpactSound)
	{
		//UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}

	FDecalData ImpactDecal = GetImpactDecal(HitSurfaceType);
	if(ImpactDecal.DecalMaterial)
	{
		FRotator RandomDecalRotation = SurfaceHit.ImpactNormal.Rotation();
		RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

		//@todo: 특정 상황에서 안그려지는 문제가 있음
		UGameplayStatics::SpawnDecalAttached(ImpactDecal.DecalMaterial, FVector(1.0f, ImpactDecal.DecalSize, ImpactDecal.DecalSize),
			SurfaceHit.Component.Get(), SurfaceHit.BoneName,
			SurfaceHit.ImpactPoint, RandomDecalRotation, EAttachLocation::KeepWorldPosition,
			ImpactDecal.LifeSpan);
		//UGameplayStatics::SpawnDecalAtLocation(this, ImpactDecal.DecalMaterial, FVector(1.0f, ImpactDecal.DecalSize, ImpactDecal.DecalSize), SurfaceHit.ImpactPoint, SurfaceHit.ImpactNormal.Rotation(), ImpactDecal.LifeSpan);
	}

}


UParticleSystem * ASZImpactEffect::GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	UParticleSystem* ImpactFX = NULL;

	switch (SurfaceType)
	{
		case SZ_SURFACE_Rock:		ImpactFX = RockFx; break;
		case SZ_SURFACE_Sand:		ImpactFX = SandFx; break;
		case SZ_SURFACE_Cloth:		ImpactFX = ClothFx; break;
		case SZ_SURFACE_Concrete:	ImpactFX = ConcreateFx; break;
		case SZ_SURFACE_Water:		ImpactFX = WaterFx; break;
		case SZ_SURFACE_Metal:		ImpactFX = MetalFx; break;
		case SZ_SURFACE_Wood:		ImpactFX = WoodFx; break;
		case SZ_SURFACE_Grass:		ImpactFX = GrassFx; break;
		case SZ_SURFACE_Glass:		ImpactFX = GlassFx; break;
		case SZ_SURFACE_Asphalt:	ImpactFX = AsphaltFx; break;
		case SZ_SURFACE_Cardboard:	ImpactFX = CardboardFx; break;
		case SZ_SURFACE_Brick:		ImpactFX = BrickFx; break;
		case SZ_SURFACE_Flesh:		ImpactFX = FleshFx; break;
		default:					ImpactFX = DefaultFx; break;
	}

	return ImpactFX;
}

USoundBase * ASZImpactEffect::GetImpactSound(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	USoundBase* ImpactSound = NULL;

	switch (SurfaceType)
	{
		case SZ_SURFACE_Rock:		ImpactSound = RockSound; break;
		case SZ_SURFACE_Sand:		ImpactSound = SandSound; break;
		case SZ_SURFACE_Cloth:		ImpactSound = ClothSoind; break;
		case SZ_SURFACE_Concrete:	ImpactSound = ConcreateSound; break;
		case SZ_SURFACE_Water:		ImpactSound = WaterSound; break;
		case SZ_SURFACE_Metal:		ImpactSound = MetalSound; break;
		case SZ_SURFACE_Wood:		ImpactSound = WoodSound; break;
		case SZ_SURFACE_Grass:		ImpactSound = GrassSound; break;
		case SZ_SURFACE_Glass:		ImpactSound = GlassSound; break;
		case SZ_SURFACE_Asphalt:	ImpactSound = AsphaltSound; break;
		case SZ_SURFACE_Cardboard:	ImpactSound = CardboardSound; break;
		case SZ_SURFACE_Brick:		ImpactSound = BrickSound; break;
		case SZ_SURFACE_Flesh:		ImpactSound = FleshSound; break;
		default:					ImpactSound = DefaultSound; break;
	}

	return ImpactSound;
}

FDecalData  ASZImpactEffect::GetImpactDecal(TEnumAsByte<EPhysicalSurface> SurfaceType)  const
{
	FDecalData ImpactDecal;

	switch (SurfaceType)
	{
		case SZ_SURFACE_Rock:		ImpactDecal = RockDecal; break;
		case SZ_SURFACE_Sand:		ImpactDecal = SandDecal; break;
		case SZ_SURFACE_Cloth:		ImpactDecal = ClothDecal; break;
		case SZ_SURFACE_Concrete:	ImpactDecal = ConcreateDecal; break;
		case SZ_SURFACE_Water:		ImpactDecal = WaterDecal; break;
		case SZ_SURFACE_Metal:		ImpactDecal = MetalDecal; break;
		case SZ_SURFACE_Wood:		ImpactDecal = WoodDecal; break;
		case SZ_SURFACE_Grass:		ImpactDecal = GrassDecal; break;
		case SZ_SURFACE_Glass:		ImpactDecal = GlassDecal; break;
		case SZ_SURFACE_Asphalt:	ImpactDecal = AsphaltDecal; break;
		case SZ_SURFACE_Cardboard:	ImpactDecal = CardboardDecal; break;
		case SZ_SURFACE_Brick:		ImpactDecal = BrickDecal; break;
		case SZ_SURFACE_Flesh:		ImpactDecal = FleshDecal; break;
		default:					ImpactDecal = DefaultDecal; break;
	}

	return ImpactDecal;
}
