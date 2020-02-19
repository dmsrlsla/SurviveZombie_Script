// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SZInventorySlotWidget.h"
#include "SZInventoryWidget.generated.h"

/**
 * 
 */

class UInventorySlotWidget;

UCLASS()
class SZ_API USZInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = UI)
	void ShowSlotUI();
	
	UFUNCTION(BlueprintImplementableEvent, Category = UI)
	void HideSlotUI();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> ItemsArray;

	TArray<UInventorySlotWidget*> SlotArray;

	virtual void NativeConstruct() override;
};
