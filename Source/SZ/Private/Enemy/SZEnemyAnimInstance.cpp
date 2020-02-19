// Fill out your copyright notice in the Description page of Project Settings.


#include "SZEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"


void USZEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(TryGetPawnOwner());
	if (MyZombie && MyZombie->IsValidLowLevel())
	{
		CurrentState = MyZombie->CurrentState;
		Speed = MyZombie->GetCharacterMovement()->Velocity.Size();
	}
}

void USZEnemyAnimInstance::AnimNotify_CheckAttack(UAnimNotify* Notify)
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("공격 체크"));

}