// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
#include "SZTypes.h"
#include "Animation/AnimInstance.h"
#include "SZPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SZ_API USZPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USZPlayerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EStateCharacterEnum eAnimEnum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AimYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AimPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFire;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float flBlendMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float TestYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FTransform trHand_Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	FTransform trHand_Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hand, Meta = (AllowPrivateAccess = true))
	bool IsHeadMountEnable;
};
