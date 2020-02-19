// Fill out your copyright notice in the Description page of Project Settings.


#include "SZWidgetActor.h"
#include "Components/WidgetComponent.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnrealNetwork.h"

// Sets default values
ASZWidgetActor::ASZWidgetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetDrawSize(FVector2D(1920.0f, 1080.0f));

	//bReplicates = true;
}

//void ASZWidgetActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	//DOREPLIFETIME(ASZWidgetActor, WidgetComponent);
//}
// Called when the game starts or when spawned
void ASZWidgetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASZWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

