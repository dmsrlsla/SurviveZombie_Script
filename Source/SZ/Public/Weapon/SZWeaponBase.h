// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
#include "SZTypes.h"
#include "GameFramework/Actor.h"
#include "SZWeaponBase.generated.h"

class UAnimMontage;
class ASZCharacter;
class UAudioComponent;
class UParticleSystemComponent;
class USoundBase;
class ASZClipBase;

//#define COLLISION_WEAPON	ECC_GameTraceChannel1

namespace EWeaponState
{
	enum Type
	{
		Idle,
		Firing,
		//Reloading,
		Equipping,
	};
}

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	/** inifite ammo for reloads */
	//UPROPERTY(EditDefaultsOnly, Category = Ammo)
	//bool bInfiniteAmmo;
	//
	///** infinite ammo in clip, no reload required */
	//UPROPERTY(EditDefaultsOnly, Category = Ammo)
	//bool bInfiniteClip;

	/** max ammo */
	//UPROPERTY(EditDefaultsOnly, Category = Ammo)
	//int32 MaxAmmo;
	//
	///** clip size */
	//UPROPERTY(EditDefaultsOnly, Category = Ammo)
	//int32 AmmoPerClip;
	//
	///** initial clips */
	//UPROPERTY(EditDefaultsOnly, Category = Ammo)
	//int32 InitialClips;

	/** time between two consecutive shots */
	UPROPERTY(EditDefaultsOnly, Category = WeaponStat)
	float TimeBetweenShots;

	/** defaults */
	FWeaponData()
	{
		//bInfiniteAmmo = false;
		//bInfiniteClip = false;
		//MaxAmmo = 100;
		//AmmoPerClip = 20;
		//InitialClips = 4;
		TimeBetweenShots = 0.2f;
		//NoAnimReloadDuration = 1.0f;
	}
};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	/** animation played on pawn (1st person view) */
	//UPROPERTY(EditDefaultsOnly, Category = Animation)
	//UAnimMontage* Pawn1P;

	/** animation played on pawn (3rd person view) */
	//UPROPERTY(EditDefaultsOnly, Category = Animation)
	//UAnimMontage* Pawn3P;
};

UCLASS(Abstract, Blueprintable)
class   ASZWeaponBase : public AActor
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents()override;

	virtual void Destroyed() override;

	///////////////////////////////////////////////////////////////////
	//Ammo

	enum class EAmmoType
	{
		EBullet
	};

	//[server] add ammo
	void GiveAmmo(int AddAmount);

	/** consume a bullet */
	void UseAmmo();

	virtual EAmmoType GetAmmoType() const
	{
		return EAmmoType::EBullet;
	}

	///////////////////////////////////////////////////////////////////
	//Inventory

	//virtual void OnEquip(const ASZCharacter* LastWeapon);
	//
	//virtual void OnEquipFinished();
	//
	//virtual void OnUnEquip();
	//
	//virtual void OnEnterInventory(ASZCharacter* NewOwner);
	//
	//virtual void OnLeaveInventory();
	//
	//bool IsEquipped() const;
	//
	//bool IsAttachedToPawn();

	///////////////////////////////////////////////////////////////////
	//Input

	/** [local + server] start weapon fire */
	virtual void StartFire();

	/** [local + server] stop weapon fire */
	virtual void StopFire();

	virtual void StartReload();

	//UFUNCTION(reliable, client)
	//void ClientStartReload();*/


	///////////////////////////////////////////////////////////////////
	//Control

	bool CanFire() const;



	///////////////////////////////////////////////////////////////////
	//Read Data
public:
	EWeaponState::Type GetCurrentState() const;

	//int32 GetCurrentAmmo() const;

	//int32 GetCurrentAmmoInClip() const;

	int32 GetAmmoPerClip() const;

	//int32 GetMaxAmmo() const;

	USkeletalMeshComponent* GetWeaponMesh() const;


protected:
	/** get pawn owner */
	UFUNCTION(BlueprintCallable, Category = "Game|Weapon")
	class ASZCharacter* GetPawnOwner() const;

	UPROPERTY(Transient)
	float TimerIntervalAdjustment;

	
	UPROPERTY(Config)
	bool bAllowAutomaticWeaponCatchup = true;

	bool HasInfiniteAmmo() const;

	bool HasInfiniteClip()const;


	//bool HasInfiniteAmmo() const;

	


protected:
	/** pawn owner */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_MyPawn)
	class ASZCharacter* MyPawn;

	/** weapon data */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponData WeaponConfig;

private:
	/** weapon mesh: 1st person view */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* Mesh1P;

	/** weapon mesh: 3rd person view */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh3P;

protected:

	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	FName MuzzleAttachPoint;


	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	//single fire sound
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* FireLoopSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* FireFinishSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* OutOfAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundBase* EquipSound;

	//UPROPERTY(EditDefaultsOnly, Category = Animation)
	//FWeaponAnim ReloadAnim;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FWeaponAnim EquipAnim;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	FWeaponAnim FireAnim;

	//is muzzle FX looped?
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	uint32 bLoopedMuzzleFX : 1;

	//is fire sound looped? 
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	uint32 bLoopedFireSound : 1;

	//is fire Animation looped?
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	uint32 bLoopedFireAnim : 1;

	//is fire animation playing?
	uint32 bPlayingFireAnim : 1;

	//is weapon current equipped?
	uint32 bIsEquipped : 1;

	//is weapon fire active? 
	uint32 bWantsToFire : 1;

	//is equip animation playing?
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_Reload)
	//uint32 bPendingReload : 1;

	//is equip animation playing?
	//uint32 bPendingEquip : 1;

	// weapon is refiring 
	uint32 bRefiring;

	EWeaponState::Type CurrentState;

	float LastFireTime;

	//UPROPERTY(Transient, Replicated)
	//int32 CurrentAmmo;
	
	//UPROPERTY(Transient, Replicated)
	//int32 CurrentAmmoInClip;

	/** burst counter, used for replicating fire events to remote clients */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_BurstCounter)
	int32 BurstCounter;

	FTimerHandle TimerHandle_HandleFiring;

	///////////////////////////////////////////////////////////////////
	// Input - server side

	UFUNCTION(reliable, server, WithValidation)
	void ServerStartFire();

	UFUNCTION(reliable, server, WithValidation)
	void ServerStopFire();

	UFUNCTION(reliable, server, WithValidation)
	void ServerStartReload();
	//
	//UFUNCTION(reliable, server, WithValidation)
	//void ServerStopReload();

	///////////////////////////////////////////////////////////////////
	// Replication & effects

	UFUNCTION()
	void OnRep_MyPawn();

	UFUNCTION()
	void OnRep_BurstCounter();

	UFUNCTION()
	void OnRep_CurrentClip();

	//UFUNCTION()
	//void OnRep_Reload();

	// Called in network play to do the cosmetic fx for firing 
	virtual void SimulateWeaponFire();

	// Called in network play to stop cosmetic fx (e.g. for a looping shot). 
	virtual void StopSimulatingWeaponFire();

	///////////////////////////////////////////////////////////////////
	// Weapon usage

	// [local] weapon specific fire implementation 
	virtual void FireWeapon() PURE_VIRTUAL(ASZWeaponBase::FireWeapon,);

	// [server] fire & update ammo 
	UFUNCTION(reliable, server, WithValidation)
	void ServerHandleFiring();

	//[local + server] handle weapon refire, compensating for slack time if the timer can't sample fast enough
	void HandleReFiring();

	//[local + server] handle weapon fire
	void HandleFiring();

	//[local + server] firing started
	virtual void OnBurstStarted();

	//[local + server] firing finished
	virtual void OnBurstFinished();

	//update weapon state
	void SetWeaponState(EWeaponState::Type NewState);

	//determine current weapon state
	void DetermineWeaponState();

	//////////////////////////////////////////////////////////////////////////
	// Inventory

	//void AttachMeshPawn();

	//void DetachMeshFromPawn();

	//////////////////////////////////////////////////////////////////////////
	// Weapon usage helpers

	UAudioComponent* PlayWeaponSound(USoundBase* Sound);

	//float PlayWeaponAnimation(const FWeaponAnim& Animation);
	//
	//void StopWeaponAnimation(const FWeaponAnim& Animation);

	//Get the aim of the weapon, allowing for adjustments to be made by the weapon
	//virtual FVector GetAdjustedAim() const;

	/** Get the aim of the camera */
	FVector GetWeaponAim() const;

	/** get the originating location for camera damage */
	FVector GetWeaponDamageStartLocation(const FVector& AimDir) const;

	/** get the muzzle location of the weapon */
	FVector GetMuzzleLocation() const;

	/** get direction of weapon's muzzle */
	FVector GetMuzzleDirection() const;

	/** find hit */
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;


	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName ClipAttachPoint;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Weapon)
	UBoxComponent* WeaponCollision;

	//UFUNCTION()
	//void EquipWeapon(USceneComponent * AttachTo);

	bool IsEquip = false;

public:
	void SetOwningPawn(ASZCharacter* ASZCharacter);

	void SetOwningClip(ASZClipBase* NewOwner);

	FName GetClipAttachPoint() const;

	void SetEquipping();

	UPROPERTY(EditAnywhere, Category = "PickupProperties")
	UTexture2D* PickupTexture;

	/*Returns the Texture of our Pickup*/
	FORCEINLINE UTexture2D* GetPickupTexture() { return PickupTexture; }

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	bool GetEquip();

	UPROPERTY(transient, ReplicatedUsing = OnRep_CurrentClip)
	ASZClipBase* CurrentClip;
};
