// Fill out your copyright notice in the Description page of Project Settings.


#include "SZEnemySpawner.h"
#include "Components/BoxComponent.h"
#include "SZEnemyBase.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundBase.h"
#include "SZAIController.h"



// Sets default values
ASZEnemySpawner::ASZEnemySpawner(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Spawner = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this,TEXT("Spawner"));
	Spawner->SetupAttachment(RootComponent);
	TriggerBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	//RootComponent = Spawner;
	IsUsed = false;

}

void ASZEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerBox)
	{
		TriggerBox->SetGenerateOverlapEvents(true);
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASZEnemySpawner::OnOverlapBegin);
	}

	
}

void ASZEnemySpawner::SetSpawningActive(bool bShouldSpawn)
{
	IsUsed = bShouldSpawn;

	if (IsUsed)
	{
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASZEnemySpawner::SpawnEnemy, SpawnData.SpawnDelay, false);

		// 트리거 작동 시 유저에게 소리로 정보전달
		if (TriggerSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), TriggerSound, 1.f, 1.f, 0.f, nullptr, this);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void ASZEnemySpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("Player"))) && IsUsed == false)
	{
		SetSpawningActive(true);
	}
}


void ASZEnemySpawner::SpawnEnemy()
{
	if (Role == ROLE_Authority)
	{
		const FVector& SpawnOrigin = Spawner->Bounds.Origin;
		const FVector& SpawnExtent = Spawner->Bounds.BoxExtent;

		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
		
		ASZEnemyBase * Zombie = IsChaser? 
			GetWorld()->SpawnActor<ASZEnemyBase>(ChaserEnemy, FVector(SpawnLocation.X, SpawnLocation.Y, Spawner->GetComponentLocation().Z), FRotator::ZeroRotator) 
			:GetWorld()->SpawnActor<ASZEnemyBase>(NormalEnemy, FVector(SpawnLocation.X, SpawnLocation.Y, Spawner->GetComponentLocation().Z), FRotator::ZeroRotator);

		if (Zombie->IsValidLowLevel())
		{
			SpawnedCount++;
			Zombie->SetEnemyMaxHealth(SpawnData.EnemyMaxHealth);
		}
		if (SpawnedCount <= SpawnData.EnemyNum - 1)
		{
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASZEnemySpawner::SpawnEnemy, SpawnData.TimeBetweenSpawn, false);
		}
	}
}



