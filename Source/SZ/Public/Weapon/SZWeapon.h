// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SZ.h"
//
#include "GameFramework/Actor.h"
#include "SZWeapon.generated.h"

UCLASS()
class SZ_API ASZWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASZWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Weapon)
	UBoxComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UStaticMeshComponent* WeaponMesh;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
