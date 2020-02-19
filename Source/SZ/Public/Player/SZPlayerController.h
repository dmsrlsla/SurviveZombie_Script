// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SZPlayerController.generated.h"

class ASZHUD;

UCLASS(config=Game)
class ASZPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()
	
public:

	ASZHUD* GetSZHUD() const;

	virtual void SetPlayer(UPlayer* Player);

	virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void HandleInventoryInput();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class USZInventoryWidget> ItemWidgetClass;

	USZInventoryWidget* ItemWidget;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* aPawn) override;
};
