// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_SetRandomNextPoint.h"
#include "Enemy/SZAIController.h"
#include "Enemy/SZEnemyBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_SetRandomNextPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASZAIController* AIC = Cast<ASZAIController>(OwnerComp.GetAIOwner());
	if (AIC && AIC->GetPawn())
	{
		FVector NewDestination = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), 
			AIC->GetPawn()->GetActorLocation(),
			500.f);

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("Destination"), NewDestination);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}