// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SZInventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SZ_API USZInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* ItemTexture;

	UFUNCTION(BlueprintCallable, Category = UI)
	void SetEquippedItem();

public:
	UFUNCTION(BlueprintCallable, Category = UI)
	void SetItemTexture(AActor* Item);

	virtual void NativeConstruct() override;
};
