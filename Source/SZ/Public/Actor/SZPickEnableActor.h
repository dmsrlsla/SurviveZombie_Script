// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PackUpInterface.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "SZTypes.h"
#include "SZPickEnableActor.generated.h"

UCLASS()
class SZ_API ASZPickEnableActor : public AActor, public IPackUpInterface
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	ASZPickEnableActor();

	UPROPERTY(VisibleAnyWhere, Category = Actor)
	UStaticMeshComponent* ActorMesh; // 삼인칭 메시

	/*픽업 가능시 빛나게 함*/
	void SetGlowEffect(bool Status);

	/*Returns the Texture of our Pickup*/
	FORCEINLINE UTexture2D* GetPickupTexture(){ return PickupTexture; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Pickup_Implemetation(class USceneComponent* AttachTo);
	virtual void Drop_Implemetation();

	// 그냥 강제로 인터페이스 없이 호출하는 함수들.
	void Pickup_compulsion(class USceneComponent* AttachTo); // 집기

	void Drop_compulsion(); // 던지기

	void Reload_compulsion(class USceneComponent* AttachTo); // 재장전(탄창을 줒었을때)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemType")
	EItemEnum eItemtype;

	UPROPERTY(EditAnywhere, Category = "PickupTexture")
		UTexture2D* PickupTexture;

	UPROPERTY(EditAnywhere, Category = "PickupTexture")
		FString ItemName;
};
