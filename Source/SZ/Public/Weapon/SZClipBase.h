// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
#include "SZTypes.h"
#include "GameFramework/Actor.h"
#include "SZClipBase.generated.h"

class ASZWeaponBase;

USTRUCT()
struct FClipData
{
	GENERATED_USTRUCT_BODY()

	

	/** infinite ammo in clip, no reload required */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool bInfiniteClip;

	///** clip size */
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	int32 AmmoPerClip;


	/** defaults */
	FClipData()
	{
		bInfiniteClip = false;
		AmmoPerClip = 30;
	}
};

UCLASS(Abstract, Blueprintable)
class ASZClipBase : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents()override;

	virtual void Destroyed() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FullBody;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* EmptyBody;
protected:
	//UPROPERTY(Transient)
	//ASZWeaponBase* MyWeapon;

public:
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FClipData ClipConfig;


	void AttachMeshToWeapon(ASZWeaponBase* Weapon);

	void DetachMeshFromWeapon();

	bool IsAttachedToWeapon() const;

	uint32 bAttachedWeapon : 1;

	bool bAttachedHand;

	USkeletalMeshComponent* GetFullMesh();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (BlueprintProtected = "true"))
	TSubclassOf<ASZWeaponBase> WeaponType;

	void UseAmmo();


	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName ClipAttachPoint;

	//UPROPERTY(Transient, Replicated)
	//int32 CurrentAmmo;

	/** current ammo - inside clip */
	UPROPERTY(Transient, Replicated)
	int32 CurrentAmmoInClip;


	int32 GetCurrentAmmoInClip() const;

	bool HasInfiniteClip() const;

};
