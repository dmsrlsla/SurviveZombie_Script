// Fill out your copyright notice in the Description page of Project Settings.


#include "SZPickEnableActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASZPickEnableActor::ASZPickEnableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	eItemtype = EItemEnum::Normal; // 초기화, 블루프린트에 의해서 바뀜.

	PickupTexture = CreateDefaultSubobject<UTexture2D>(FName("ItemTexture"));
}

void ASZPickEnableActor::SetGlowEffect(bool Status)
{
	ActorMesh->SetRenderCustomDepth(Status);
}

// Called when the game starts or when spawned
void ASZPickEnableActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASZPickEnableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASZPickEnableActor::Pickup_Implemetation(USceneComponent * AttachTo) // 인터페이스형. 안씀
{
	UE_LOG(LogTemp, Warning, TEXT("GetActorNearHand_PickUp7777"));
	ActorMesh->SetSimulatePhysics(false);
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	GetRootComponent()->AttachToComponent(AttachTo, AttachmentTransformRules);
}

void ASZPickEnableActor::Drop_Implemetation() // 인터페이스형. 안씀
{
	ActorMesh->SetSimulatePhysics(true);
	this->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void ASZPickEnableActor::Pickup_compulsion(USceneComponent * AttachTo) // 강제로 잡기
{
	ActorMesh->SetSimulatePhysics(false);
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	GetRootComponent()->AttachToComponent(AttachTo, AttachmentTransformRules);
}

void ASZPickEnableActor::Drop_compulsion() // 강제로 내려놓기.
{
	ActorMesh->SetSimulatePhysics(true);

	FDetachmentTransformRules DetatchmentTransformRules(EDetachmentRule::KeepWorld, true);
	DetachFromActor(DetatchmentTransformRules);
}

void ASZPickEnableActor::Reload_compulsion(USceneComponent * AttachTo)
{
	ActorMesh->SetSimulatePhysics(false); // 그냥 붙여봤음. 사실 필요없음.
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, false);
	GetRootComponent()->AttachToComponent(AttachTo, AttachmentTransformRules);
}

