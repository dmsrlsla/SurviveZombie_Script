// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SZTypes.h"
#include "SZEnemyBase.generated.h"

UCLASS()
class ASZEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ASZEnemyBase();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State", replicated)
	EEnemyState CurrentState = EEnemyState::Normal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPawnSensingComponent* PawnSensing;

	UFUNCTION()
	void SeenPawn(APawn* SeenPawn);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AI")
	class UBehaviorTree* ZombieBT;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated)
	float CurrentHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated)
	float MaxHP = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated)
	float AttackDamage = 10.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, replicated)
	int MeshID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RunSpeed = 400.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WalkSpeed = 150.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DeadSpeed = 0.0f;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EEnemyState NewState);

	UFUNCTION(BlueprintCallable)
	void SetWalkSpeed(float Speed);

	UFUNCTION(BlueprintCallable)
	void SetEnemyMaxHealth(float Health);

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* AttackSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* DeathSound;

	///////////////// Data Talbe
	UPROPERTY(EditDefaultsOnly)
	UDataTable* MeshTable;
};
