// Fill out your copyright notice in the Description page of Project Settings.


#include "SZClipSpawner.h"
#include "Components/BoxComponent.h"
#include "SZClipBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASZClipSpawner::ASZClipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spawner = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawner"));
	Spawner->SetupAttachment(RootComponent);
}


void ASZClipSpawner::ClipSpawn(UPrimitiveComponent* Attachto)
{
	ASZClipBase* Clip = GetWorld()->SpawnActor<ASZClipBase>(Clips, FVector::ZeroVector, FRotator::ZeroRotator);
	Clip->AttachToComponent(Attachto, FAttachmentTransformRules::KeepRelativeTransform);
	Clip->bAttachedHand = true;
}