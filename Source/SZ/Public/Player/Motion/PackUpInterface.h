// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PackUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UPackUpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SZ_API IPackUpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "VRTemplate|BPI_Lowlevel|Player")
	void Pickup(class USceneComponent* AttachTo);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Drop();
};
