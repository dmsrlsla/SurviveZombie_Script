// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckStateByDistance.h"
#include "Enemy/SZAIController.h"
#include "Player/SZCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_CheckStateByDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASZCharacter* Player = Cast<ASZCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (!MyZombie || !Player)
	{
		return EBTNodeResult::Failed;
	}

	float Distance = FVector::Distance(MyZombie->GetActorLocation(), Player->GetActorLocation());

	switch (Condition)
	{

		case ETaskCondition::Less:
		{
			if (Distance < Range)
			{
				MyZombie->SetCurrentState(TargetState);
			}
		}
		break;

	case ETaskCondition::Greater:
		{
			if (Distance > Range)
			{
				MyZombie->SetCurrentState(TargetState);
			}
		}
		break;
	}

	return EBTNodeResult::Succeeded;
}