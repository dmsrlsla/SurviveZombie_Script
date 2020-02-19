// Fill out your copyright notice in the Description page of Project Settings.


#include "SZWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SZPickEnableActor.h"

// Sets default values
ASZWeapon::ASZWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(WeaponMesh);
	WeaponCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	WeaponCollision->SetGenerateOverlapEvents(true);
	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ASZWeapon::OnComponentBeginOverlap);

	//WeaponMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	//WeaponMesh->SetGenerateOverlapEvents(true);
	//WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &ASZWeapon::OnComponentBeginOverlap);



	// set up a notification for when this component overlaps something  
}

// Called when the game starts or when spawned
void ASZWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASZWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASZWeapon::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherComp != nullptr) && (OtherComp != WeaponMesh))
	{
		// SomWorks :D // Cast the OverlapComponet to UStaticMeshComponent
		USkeletalMeshComponent* const MyOverlapComponent = Cast<USkeletalMeshComponent>(OtherComp);
		if (MyOverlapComponent && MyOverlapComponent->IsSimulatingPhysics())
		{
			auto AMMOActor = Cast<ASZPickEnableActor>(OtherComp);
			if (AMMOActor != nullptr)
			{
				if (AMMOActor->eItemtype == EItemEnum::Ammo) // 총알 액터라면.
				{
					AMMOActor->Reload_compulsion(WeaponMesh);
				}
			}
			else
			{
				// 에러
				UE_LOG(LogTemp, Warning, TEXT("aa"));
			}
		}
	}
}

