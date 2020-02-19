// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h"
#include "Components/SphereComponent.h"
#include "PackUpInterface.h"
#include "InteractionInterface.h"
#include "SZMotionHandController.generated.h"

UCLASS()
class SZ_API ASZMotionHandController : public AActor, public IPackUpInterface
{
	GENERATED_BODY()
	ASZMotionHandController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, Category = NearActor)
	float NearestActorDistance_PickUp;

	UPROPERTY(VisibleAnyWhere, Category = NearActor)
	float NearestActorDistance_Interaction;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* NearActor_P;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* NearActor_I;

	UPROPERTY(VisibleAnyWhere, Category = Grab)
	AActor* AttachActor;

	UPROPERTY(VisibleAnyWhere, Category = Interact)
	AActor* InterActor;

	UPROPERTY(VisibleAnyWhere, Category = Hand)
	USceneComponent* RootScene;
public:

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite, Category = Area)
	UMotionControllerComponent* MotionController;

	UPROPERTY(VisibleAnyWhere, Category = Area)
	USphereComponent* GrabShpere;

	UFUNCTION()
	AActor* GetActorNearHand_PickUp();

	UFUNCTION()
	void GrabActor();

	UFUNCTION()
	void UnGrabActor();
	// 인터페이스

	UFUNCTION()
	AActor* GetActorNearHand_Interact();

	UFUNCTION()
	void InteractionActor();

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RumbleController(float Intensity);

	UFUNCTION(BlueprintCallable, Category = "Motion Source")
		void SetupMotionSource(FName MotionSourceName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Broadcast")
	TScriptInterface<IPackUpInterface> BroadcastListener;

	void InitHand(USceneComponent* InitHand);

	virtual void OnConstruction(const FTransform & Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRTemplate|Variables")
	EControllerHand SZHand;
};
