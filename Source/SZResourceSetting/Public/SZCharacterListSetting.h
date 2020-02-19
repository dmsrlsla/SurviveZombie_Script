// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SZCharacterListSetting.generated.h"

/**
 * 
 */
UCLASS(config = SZCharacterSetting)
class SZRESOURCESETTING_API USZCharacterListSetting : public UObject
{
	GENERATED_BODY()
	
public:
	USZCharacterListSetting();

	UPROPERTY(config)
	TArray<FSoftObjectPath> ZombieChracterSetting;
};
