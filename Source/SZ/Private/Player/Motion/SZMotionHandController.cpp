// Fill out your copyright notice in the Description page of Project Settings.


#include "SZMotionHandController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Haptics/HapticFeedbackEffect_Base.h"
#include "SZPlayerController.h"
#include "SZCharacter.h"
#include "SZWeaponBase.h"
#include "SZPickEnableActor.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "SZGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SZClipbase.h"

ASZMotionHandController::ASZMotionHandController()
{
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion"));
	MotionController->SetupAttachment(RootComponent);
	GrabShpere = CreateDefaultSubobject<USphereComponent>(TEXT("GrabShpere"));

	GrabShpere->SetSphereRadius(10.0f);
	GrabShpere->SetRelativeLocation(FVector(14.286342f, 0.224237f, 1.484932f));
	GrabShpere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	GrabShpere->SetGenerateOverlapEvents(true);

	ASZPickEnableActor* LogBroadcastListener = NewObject<ASZPickEnableActor>(); // Instantiating the ULogBroadcastListener
	BroadcastListener.SetObject(LogBroadcastListener); // BroadcastListener is of type TScriptInterface
	BroadcastListener.SetInterface(Cast<IPackUpInterface>(LogBroadcastListener));

	GrabShpere->SetupAttachment(MotionController);

	SZHand = EControllerHand::Left;
}

void ASZMotionHandController::BeginPlay()
{
	Super::BeginPlay();

	NearestActorDistance_PickUp = 1000;
	NearestActorDistance_Interaction = 1000;
}

AActor * ASZMotionHandController::GetActorNearHand_PickUp()
{
	TArray<AActor*> Sphere;
	GrabShpere->GetOverlappingActors(Sphere);
	for (AActor* NewAttachActor : Sphere)
	{
		// �±װ� �Ⱦ��̳�, ���⳪, ���ͷ��� ���Ͷ��.
		if(NewAttachActor->Tags.Num() > 0) // �±װ� �ϳ��� �����ϸ�.
		{
			float NewActorDistance = UKismetMathLibrary::Vector_Distance((NewAttachActor->GetActorLocation()), (GrabShpere->GetComponentLocation()));
			if (NewActorDistance < NearestActorDistance_PickUp)
			{
				NearestActorDistance_PickUp = NewActorDistance;
				NearActor_P = NewAttachActor;
			}
		}
	}
	return NearActor_P;
}

void ASZMotionHandController::GrabActor()
{
	if (GetActorNearHand_PickUp() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Pick"));
		return;
	}
	AttachActor = GetActorNearHand_PickUp(); //ã�� ���� ��ȯ
	if (IsValid(AttachActor))
	{
		auto Character = Cast<ASZCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		// �������̽��� ã�� �ι�° ��� : ImplementsInterface�� �̿��ؼ� ã��
		if (AttachActor->ActorHasTag(TEXT("PickUp")))
		{
			ASZPickEnableActor* NewActor = Cast<ASZPickEnableActor>(AttachActor);
			NewActor->Pickup_compulsion(GrabShpere);
		}

		else if(AttachActor->ActorHasTag(TEXT("Weapon")))
		{
			ASZWeaponBase* NewWeapon = Cast<ASZWeaponBase>(AttachActor);
			if (NewWeapon && !(NewWeapon->GetEquip()))
			{
				Character->EquipWeapon(NewWeapon);
			}
		}
		else if (AttachActor->ActorHasTag(TEXT("Ammo")))
		{
			ASZClipBase* NewClip = Cast<ASZClipBase>(AttachActor);
			if (!(NewClip->bAttachedWeapon))
			{
				NewClip->GetFullMesh()->SetSimulatePhysics(false);
				FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, false);
				NewClip->GetRootComponent()->AttachToComponent(GrabShpere, AttachmentTransformRules);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("nononono Pick"));
	}
}

void ASZMotionHandController::UnGrabActor()
{
	if (GetActorNearHand_PickUp() == nullptr) return;
	AttachActor = GetActorNearHand_PickUp(); //ã�� ���� ��ȯ
	if (IsValid(AttachActor))
	{
		if (AttachActor->ActorHasTag(TEXT("PickUp")))
		{
			ASZPickEnableActor* NewActor = Cast<ASZPickEnableActor>(AttachActor);
			NewActor->Drop_compulsion();
		}
		else if (AttachActor->ActorHasTag(TEXT("Ammo")))
		{
			ASZClipBase* NewClip = Cast<ASZClipBase>(AttachActor);
			NewClip->bAttachedHand = false;
			if (!(NewClip->bAttachedWeapon))
			{
				NewClip->GetFullMesh()->SetSimulatePhysics(true);
				FDetachmentTransformRules DetatchmentTransformRules(EDetachmentRule::KeepWorld, true);
				NewClip->DetachFromActor(DetatchmentTransformRules);
			}
		}

	}
	AttachActor = nullptr;
	NearActor_P = nullptr;
	NearestActorDistance_PickUp = 100;
}

AActor * ASZMotionHandController::GetActorNearHand_Interact()
{
	TArray<AActor*> Sphere;

	GrabShpere->GetOverlappingActors(Sphere);

	for (int i = 0; i < Sphere.Num(); i++)
	{
		AActor* TestActor = Sphere[i];

		// �������̽��� ã�� ��� : UKismetSystemLibrary�� DoesImplementInterface�� �̿��ؼ� ã��
		if (AttachActor->ActorHasTag(TEXT("Interaction")))
		{
			// ���ͷ����� ��� ������ ��ĥ���� ��� �ʿ�� ������ �ϴ� ����.
			float NewActorDistance = UKismetMathLibrary::Vector_Distance((TestActor->GetActorLocation()), (GrabShpere->GetComponentLocation()));
			if (NewActorDistance < NearestActorDistance_Interaction)
			{
				NearestActorDistance_Interaction = NewActorDistance;
				NearActor_I = TestActor;
			}
		}
	}
	return NearActor_I;
}

void ASZMotionHandController::InteractionActor()
{
	if (GetActorNearHand_Interact() == nullptr) return;
	InterActor = GetActorNearHand_Interact(); //ã�� ���� ��ȯ

	if (IsValid(AttachActor))
	{
		// �������̽��� ã�� �ι�° ��� : ImplementsInterface�� �̿��ؼ� ã��(��� X)
		if (InterActor->ActorHasTag(TEXT("Interaction")))
		{
			//IInteractionInterface* ReactingObject = Cast<IInteractionInterface>(AttachActor);
			//ReactingObject->Interact(Cast<USceneComponent>(GrabShpere));
			////IPackUpInterface::Execute_PickUp(AttachActor, this);
		}
	}
}

void ASZMotionHandController::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto CheckSpawnZone = Cast<UChildActorComponent>(OtherComp);
	if (CheckSpawnZone)
	{
		auto Character = Cast<ASZCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Character->SelectedActor = CheckSpawnZone;
		Character->IsClipSpawn = true;
	}
	else
	{
		return;
	}
}
void ASZMotionHandController::SetupMotionSource(FName MotionSourceName)
{
	if (MotionSourceName == "Right")
	{
		MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	}
	else
	{
		MotionController->MotionSource = FXRMotionControllerBase::LeftHandSourceId;
	}
}
void ASZMotionHandController::RumbleController(float Intensity)
{
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
}

void ASZMotionHandController::InitHand(USceneComponent* InitHand)
{
	//GrabShpere->SetupAttachment(Hand);
	//WIC->SetupAttachment(Hand);
}

void ASZMotionHandController::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);
	MotionController->SetTrackingSource(SZHand);
}
