// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SZAIController.h"
#include "SZEnemyBase.h"
#include "SZCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "GameFramework/GameStateBase.h"
#include "TimerManager.h"


ASZAIController::ASZAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTComponent"));
	BBComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BBComponent"));
	CurrentTarget = NULL;
}

void ASZAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASZEnemyBase* Zombie = Cast<ASZEnemyBase>(InPawn);

	// start behavior
	if (Zombie && Zombie->ZombieBT)
	{
		if (Zombie->ZombieBT->BlackboardAsset)
		{
			BBComponent->InitializeBlackboard(*Zombie->ZombieBT->BlackboardAsset);
			BTComponent->StartTree(*(Zombie->ZombieBT));
		}

		SetCurrentState(EEnemyState::Normal);
		SetSpeedValue();
	}
}

void ASZAIController::OnUnPossess()
{
	BTComponent->StopTree();
	Super::OnUnPossess();
}

void ASZAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ASZAIController::SetCurrentState(EEnemyState NewState)
{
	BBComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)NewState);
}

//블랙보드에 초기값 설정
void ASZAIController::SetSpeedValue()
{
	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(GetPawn());
	if (MyZombie)
	{
		BBComponent->SetValueAsFloat(TEXT("WalkSpeed"), MyZombie->WalkSpeed);
		BBComponent->SetValueAsFloat(TEXT("RunSpeed"), MyZombie->RunSpeed);
		BBComponent->SetValueAsFloat(TEXT("DeadSpeed"), MyZombie->DeadSpeed);
	}
	
}

void ASZAIController::SetPlayer(AActor* Player)
{
	if (Player)
	{
		BBComponent->SetValueAsObject(TEXT("Enemy"), Player);
		CurrentTarget = Cast<ASZCharacter>(Player);
	}
}

