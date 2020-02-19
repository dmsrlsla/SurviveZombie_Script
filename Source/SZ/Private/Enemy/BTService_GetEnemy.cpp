// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_GetEnemy.h"
#include "Enemy/SZEnemyBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/SZAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/World.h"
#include "SZCharacter.h"


void UBTService_GetEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	int Number = FMath::RandRange(0, GetWorld()->GetGameState()->PlayerArray.Num()-1);

	ASZCharacter* PlayerPawn = Cast<ASZCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), Number));
	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (PlayerPawn->IsAlive())
	{
		ASZAIController* AIC = Cast<ASZAIController>(MyZombie->GetController());
		ASZCharacter* CurrentEnemy = AIC->CurrentTarget;

		if (AIC->CurrentTarget == NULL)
		{
			Cast<ASZAIController>(MyZombie->GetController())->SetPlayer(PlayerPawn);
			MyZombie->SetCurrentState(EEnemyState::Chase);
		}

		else if(!CurrentEnemy->IsAlive())
		{
			Cast<ASZAIController>(MyZombie->GetController())->SetPlayer(PlayerPawn);
			MyZombie->SetCurrentState(EEnemyState::Chase);
		}
		
	}
	

	

}