// Fill out your copyright notice in the Description page of Project Settings.


#include "SZPlayerAnimInstance.h"
#include "SZCharacter.h"

USZPlayerAnimInstance::USZPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	eAnimEnum = EStateCharacterEnum::Idle;
}

void USZPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASZCharacter* Character = Cast<ASZCharacter>(TryGetPawnOwner());
	if (Character != nullptr)
	{
		if (::IsValid(Character))
		{
			CurrentPawnSpeed = Character->GetCharacterMovement()->Velocity.Size();
			TestYaw = Character->GetActorRotation().Yaw;
			CurrentDirection = CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
			AimYaw = Character->GetAimOffset().Yaw;
			AimPitch = Character->GetAimOffset().Pitch;
			bIsFire = Character->bIsFire;
			if (Character->MC_Left != nullptr && Character->MC_Right != nullptr)
			{
				trHand_Left = Character->MC_Left->MotionController->GetComponentTransform();
				trHand_Right = Character->MC_Right->MotionController->GetComponentTransform();
			}
			IsHeadMountEnable = Character->bUsingMotionControllers;
		}
		if (Character->eStatecharacter == EStateCharacterEnum::Move)
		{
			eAnimEnum = Character->eStatecharacter;
		}
		else
		{
			eAnimEnum = Character->eStatecharacter;
		}
	}
}