// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SZTypes.h"
#include "SZClipSpawner.generated.h"



UCLASS()
class ASZClipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZClipSpawner();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (BlueprintProtected = "true"))
	TSubclassOf<class ASZClipBase> Clips;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (BlueprintProtected = "true"))
	EAmmoTypeEnum AmmoType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)
	class UBoxComponent * Spawner;



	UFUNCTION()
	void ClipSpawn(UPrimitiveComponent* Attachto);


};
