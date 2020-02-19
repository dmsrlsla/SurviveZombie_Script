// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Enemy/SZEnemyBase.h"
#include "SZTypes.h"
#include "BTTask_CheckStateByDistance.generated.h"

UENUM(BlueprintType)
enum class ETaskCondition : uint8
{
	Less	= 0 UMETA(Display = "<"),
	Greater = 1 UMETA(Display = ">"),
};

UCLASS()
class UBTTask_CheckStateByDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Range;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ETaskCondition Condition;

	UPROPERTY(BluePrintReadOnly, EditAnywhere)
	EEnemyState TargetState;
};
