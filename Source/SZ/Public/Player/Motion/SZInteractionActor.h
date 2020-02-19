// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "SZInteractionActor.generated.h"

UCLASS()
class SZ_API ASZInteractionActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZInteractionActor();
	bool bIsOpen;
	float flTime;
	UPROPERTY(VisibleAnyWhere, Category = Actor)
	UStaticMeshComponent* ActorMesh; // »ïÀÎÄª ¸Þ½Ã

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implemetation(class USceneComponent* AttachTo);
};
