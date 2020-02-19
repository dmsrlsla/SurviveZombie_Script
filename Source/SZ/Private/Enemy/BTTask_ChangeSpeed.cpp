// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ChangeSpeed.h"
#include "Enemy/SZEnemyBase.h"
#include "Enemy/SZAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_ChangeSpeed::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ASZAIController* AIC = Cast<ASZAIController>(OwnerComp.GetAIOwner());
	if (AIC)
	{
		float NewSpeed = AIC->BBComponent->GetValueAsFloat(GetSelectedBlackboardKey());
	
		ASZEnemyBase* Pawn = Cast<ASZEnemyBase>(AIC->GetPawn());
		if (Pawn)
		{
			Pawn->SetWalkSpeed(NewSpeed);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
