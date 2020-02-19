// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SZAIController.generated.h"

UCLASS()
class ASZAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASZAIController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBlackboardComponent* BBComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBehaviorTreeComponent* BTComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBehaviorTreeComponent* BT_Wave;

	virtual void OnPossess(class APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void SetCurrentState(EEnemyState NewState);

	void SetSpeedValue();

	UFUNCTION(BlueprintCallable)
	void SetPlayer(AActor* Player);

	UPROPERTY()
	class ASZCharacter* CurrentTarget;



};
