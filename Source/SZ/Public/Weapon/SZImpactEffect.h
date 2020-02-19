// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZTypes.h"
#include "GameFramework/Actor.h"
#include "SZImpactEffect.generated.h"



UCLASS(Abstract ,Blueprintable)
class ASZImpactEffect : public AActor
{
	GENERATED_UCLASS_BODY()
		
	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	UParticleSystem* DefaultFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* RockFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* SandFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* ClothFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* ConcreateFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* WaterFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* MetalFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* WoodFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* GrassFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* GlassFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* AsphaltFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* CardboardFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* BrickFx;

	UPROPERTY(EditDefaultsOnly, Category = Visual)
	UParticleSystem* FleshFx;


//Sound

	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	class USoundBase* DefaultSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* RockSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* SandSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* ClothSoind;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* ConcreateSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* WaterSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* MetalSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* WoodSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* GrassSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* GlassSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* AsphaltSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* CardboardSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* BrickSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* FleshSound;


//Decal

	UPROPERTY(EditDefaultsOnly, Category = Defaults)
	struct	FDecalData DefaultDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData RockDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData SandDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData ClothDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData ConcreateDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData WaterDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData MetalDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData WoodDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData GrassDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData GlassDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData AsphaltDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData CardboardDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData BrickDecal;

	UPROPERTY(EditDefaultsOnly, Category = Decal)
	FDecalData FleshDecal;

	UPROPERTY(BlueprintReadOnly, Category = Surface)
	FHitResult SurfaceHit;

	virtual void PostInitializeComponents()override;

protected:

	UParticleSystem* GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType)	const;

	USoundBase* GetImpactSound(TEnumAsByte<EPhysicalSurface>SurfaceType) const;

	FDecalData GetImpactDecal(TEnumAsByte<EPhysicalSurface>SurfaceType)const;
};
