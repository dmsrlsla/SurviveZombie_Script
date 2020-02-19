// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
#include "SZTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SZMotionHandController.h"
#include "SZProjectile.h"
#include "Camera/CameraComponent.h"
#include "SZPickEnableActor.h"
#include "SZCharacter.generated.h"

#define MAX_INVENTORY_ITEMS 3 // 최대 아이템 슬롯 개수.

class ASZPickEnableActor;
class ASZWeaponBase;
class ASZClipBase;
class ASZMotionHandController;
class ASZClipSpawner;

UCLASS()
class SZ_API ASZCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASZCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** spawn inventory, setup initial variables */
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
		float RaycastRange = 500.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnyWhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MoveAnimSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = Pawn)
	EStateCharacterEnum eStatecharacter;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetAnimState(EStateCharacterEnum NewState);

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Hand)
	USceneComponent* VR_Origin;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class ASZMotionHandController* MC_Left;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class ASZMotionHandController* MC_Right;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//class ASZClipSpawner* ClipSpawn_M4;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//class ASZClipSpawner* ClipSpawn_SMG;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//class ASZClipSpawner* ClipSpawn_AKU;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UChildActorComponent* ClipSpawn_Actor_M4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UChildActorComponent* ClipSpawn_Actor_SMG;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UChildActorComponent* ClipSpawn_Actor_AKU;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UChildActorComponent* SelectedActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	ASZClipSpawner* ClipSpawnerTemp;

	bool IsClipSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (BlueprintProtected = "true"))
	TSubclassOf<ASZMotionHandController> MCT;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* UAGrabActor;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* Hand_L;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* Hand_R;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_CurrentWeapon)
	class ASZWeaponBase* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (BlueprintProtected = "true"))
	TSubclassOf<ASZWeaponBase> WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Weapon, meta = (BlueprintProtected = "true"))
	TSubclassOf<ASZClipBase> ClipType;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsGrab;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ASZProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	/** check if pawn is still alive */
	bool IsAlive() const;

	bool IsEnemyFor(AController* TestPC) const;

	/** get max health */
	int32 GetMaxHealth() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = Health)
	float Health;

	UFUNCTION()
	void EquipWeapon(ASZWeaponBase* WeaponActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = Health)
	bool bEquipWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = Health)
	bool bIsInGame;

	UFUNCTION()
	void SetAnimState(EStateCharacterEnum newState);

	FRotator GetAimOffset() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	bool bIsFire;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIsFire(bool IsFire);

	UFUNCTION()
	void WeaponItemSelect(); // 아이템 셀렉트

	UFUNCTION()
	void UnWeaponItemSelect(); // 아이템 셀렉트

	UFUNCTION()
	void ItemPickUp();

	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<AActor* > WeaponInventory;

	UPROPERTY(VisibleAnywhere, Replicated)
	TArray<AActor* > AmmoInventory;

	//ASZWeaponBase* TestSeenItem;
	UPROPERTY(Replicated)
	AActor* LastSeenItem;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerItemDestroy();

	UPROPERTY(Replicated)
	int32 SelectItemNum;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void ReloadOverlap(AActor* AmmoActor);

	UFUNCTION()
	void OnBeginOverlapLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapLeftHand(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void SetAmmoPlus(EAmmoTypeEnum AmmoType, int Count);


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int AmmoCount_M4;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int AmmoCount_SMG;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int AmmoCount_AKU;

private:

	void MoveForward(float flAxisValue);

	void MoveRight(float flAxisValue);

	void CameraY(float flAxisValue);

	void CameraX(float flAxisValue);

	void DoFire();

	void UnFire();

	void DoReload();

	void UnReload();

	void IdleState();

	void MoveState();

	void AttackState();
	
	void DeathState();

	void HitState();

	void InteractionState();

	void ReloadState();

	void MoveAttackState();

	UFUNCTION()
	void GrabActorL(); //왼손집기
	UFUNCTION()
	void GrabActorR(); // 오른손집기
	UFUNCTION()
	void UnGrabActorL(); // 왼손버리기(현재는 놓으면 놓는걸로 세팅)
	UFUNCTION()
	void UnGrabActorR(); // 오른손 버리기(현재는 놓으면 놓는걸로 세팅)


	/** play anim montage */

	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/** stop playing montage */

	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	/*Raycasts in front of the character to find usable items*/
	void Raycasting();

	void ResetCameraPos();

	//bool bBtnGrap;

	//bool bBtnFire;

	//bool bBtnChangeItem;
};
