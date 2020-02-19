// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetInteractionComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AMainMenuPawn::AMainMenuPawn()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VR_Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));

	//Left_MotionHandController = CreateDefaultSubobject<ASZMotionHandController>(TEXT("Left_MotionHandController"));
	//
	//Right_MotionHandController = CreateDefaultSubobject<ASZMotionHandController>(TEXT("Right_MotionHandController"));


	//Left_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftMesh"));
	//Right_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightMesh"));

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> HandMesh(TEXT("SkeletalMesh'/Game/Character/Mesh/MannequinHand_Right.MannequinHand_Right'"));

	//if (HandMesh.Object != nullptr)
	//{
	//	Left_Mesh->SetSkeletalMesh(HandMesh.Object);
	//	Right_Mesh->SetSkeletalMesh(HandMesh.Object);
	//}

	FTransform OriginTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));

	VR_Origin->SetWorldTransform(OriginTransform);
	VR_Origin->SetupAttachment(RootComponent);

	//Left_MotionHandController->MotionController->SetupAttachment(VR_Origin);
	//Right_MotionHandController->MotionController->SetupAttachment(VR_Origin);
}

// Called when the game starts or when spawned
void AMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//const FTransform SpawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	//FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	//Left_MotionHandController = GetWorld()->SpawnActorDeferred<ASZMotionHandController>(ASZMotionHandController::StaticClass(), SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//Left_MotionHandController->MotionController->MotionSource = FXRMotionControllerBase::LeftHandSourceId; // 블루프린트는 Enum
	//Left_MotionHandController->MotionController->SetCollisionProfileName(TEXT("NoCollision"));
	//Left_MotionHandController->Hand = EControllerHand::Left;
	//Left_MotionHandController->FinishSpawning(SpawnTransform);
	//Left_MotionHandController->AttachToComponent(VR_Origin, AttachRules);

	//Right_MotionHandController = GetWorld()->SpawnActorDeferred<ASZMotionHandController>(ASZMotionHandController::StaticClass(), SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	//Right_MotionHandController->MotionController->SetCollisionProfileName(TEXT("NoCollision"));
	//Right_MotionHandController->MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId; // 블루프린트는 Enum 형식이라 참 쉽더라
	//Right_MotionHandController->Hand = EControllerHand::Right;
	//Right_MotionHandController->FinishSpawning(SpawnTransform);
	//Right_MotionHandController->AttachToComponent(VR_Origin, AttachRules);

	//Left_Mesh->AttachToComponent(Left_MotionHandController->MotionController, AttachRules);
	//Right_Mesh->AttachToComponent(Right_MotionHandController->MotionController, AttachRules);
}

// Called every frame
void AMainMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainMenuPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}




