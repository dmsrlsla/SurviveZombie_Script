// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
#include "SZTypes.h"
#include "GameFramework/Actor.h"
#include "SZEnemySpawner.generated.h"

USTRUCT()
struct FSpawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,Category = Spawner)
	int EnemyNum;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float TimeBetweenSpawn;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float SpawnDelay;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float EnemyMaxHealth;

	FSpawnData()
	{
		EnemyNum = 20;
		TimeBetweenSpawn = 0.8f;
		SpawnDelay = 10.0f;
		EnemyMaxHealth = 100.f;
	}
};


UCLASS(Abstract, Blueprintable)
class  ASZEnemySpawner : public AActor
{
	GENERATED_UCLASS_BODY()
	

protected:
	UPROPERTY(EditAnywhere,Category = Settings)
	FSpawnData SpawnData;

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Settings, meta = (BlueprintProtected = "true"))
	TSubclassOf<class ASZEnemyBase> NormalEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (BlueprintProtected = "true"))
	TSubclassOf<class ASZEnemyBase> ChaserEnemy;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)
	class UBoxComponent * Spawner;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Settings)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	class USoundBase* TriggerSound;


	UPROPERTY(EditAnywhere, Category = Settings)
	bool IsChaser;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (EditCondition = "!IsChaser"))
	float PawnSensingDistance = 1250.f;

	void SpawnEnemy();

	bool IsUsed;

	virtual void BeginPlay()override;

	FTimerHandle SpawnTimer;

	int	SpawnedCount = 0;

	UFUNCTION(BlueprintCallable)
	void SetSpawningActive(bool bShouldSpawn);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
