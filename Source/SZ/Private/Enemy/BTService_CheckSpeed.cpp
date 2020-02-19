// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckSpeed.h"
#include "Enemy/SZEnemyBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/SZAIController.h"

void UBTService_CheckSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (MyZombie)
	{
		if (MyZombie->CurrentState == EEnemyState::Dead)
		{
			MyZombie->SetWalkSpeed(MyZombie->DeadSpeed);
		}
		else if (MyZombie->CurrentState == EEnemyState::Chase)
		{
			MyZombie->SetWalkSpeed(MyZombie->RunSpeed);
		}
	}
}