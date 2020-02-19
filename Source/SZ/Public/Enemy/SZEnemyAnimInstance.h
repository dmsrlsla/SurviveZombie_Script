// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enemy/SZEnemyBase.h"
#include "SZTypes.h"
#include "SZEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class USZEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	EEnemyState CurrentState;

	UFUNCTION()
	void AnimNotify_CheckAttack(UAnimNotify* Notify);
	
};
