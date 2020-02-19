// Fill out your copyright notice in the Description page of Project Settings.


#include "SZInteractionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
ASZInteractionActor::ASZInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
}

// Called when the game starts or when spawned
void ASZInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	bIsOpen = false;
	flTime = 0;
}

// Called every frame
void ASZInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpen)
	{
		ActorMesh->AddRelativeRotation(FRotator(0, 90 * (DeltaTime / 2), 0));
		flTime += DeltaTime;
		if (flTime > 2)
		{
			flTime = 0;
			bIsOpen = false;
		}
	}

}

void ASZInteractionActor::Interact_Implemetation(USceneComponent * AttachTo)
{
	//FTimer
	//// 일단 문여는 동작만
	//ActorMesh->AddRelativeRotation( )
	////AStaticMesh* Actor = Cast<AStaticMesh>(AttachTo);
	bIsOpen = true;
}

