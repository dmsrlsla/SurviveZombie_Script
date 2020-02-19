// Fill out your copyright notice in the Description page of Project Settings.


#include "SZEnemyBase.h"
#include "SZ.h"
#include "SZAIController.h"
#include "Net/UnrealNetwork.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Engine/StreamableManager.h"




ASZEnemyBase::ASZEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ASZAIController::StaticClass();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	
	MeshID = 0;
	AttackDamage = 10.f;
	bReplicates = true;
}

void ASZEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	
	CurrentHP = MaxHP;
	SetCurrentState(EEnemyState::Normal);

	if (MeshTable)
	{
		if (HasAuthority())
		{
			MeshID = FMath::RandRange(1, 8);
		}

		//동적 동기 로딩
		FStreamableManager Loader;
		FZombieAssetTable* Data = MeshTable->FindRow<FZombieAssetTable>(FName(*FString::FromInt(MeshID)), TEXT("Index"));
		GetMesh()->SetSkeletalMesh(Loader.LoadSynchronous<USkeletalMesh>(Data->AssetPath));
	}

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &ASZEnemyBase::SeenPawn);
	}
	
}

void ASZEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ASZEnemyBase::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASZEnemyBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME(ASZEnemyBase, CurrentHP);
	DOREPLIFETIME(ASZEnemyBase, MaxHP);
	DOREPLIFETIME(ASZEnemyBase, CurrentState);
	DOREPLIFETIME(ASZEnemyBase, AttackDamage);
	DOREPLIFETIME(ASZEnemyBase, MeshID);


}

void ASZEnemyBase::SeenPawn(APawn * SeenPawn)
{
	if (Cast<ASZCharacter>(SeenPawn)->IsAlive())
	{
		if (CurrentState == EEnemyState::Normal)
		{
			UE_LOG(LogClass, Warning, TEXT("Seen %s"), *SeenPawn->GetName());
			SetCurrentState(EEnemyState::Chase);
			ASZAIController* AIC = Cast<ASZAIController>(GetController());
			if (AIC)
			{
				AIC->SetPlayer(SeenPawn);
			}
		}

		else if (CurrentState == EEnemyState::Battle)
		{
			SetCurrentState(EEnemyState::Normal);
		}
	}
	
}

float ASZEnemyBase::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (DamageEvent.GetTypeID() == FPointDamageEvent::ClassID)
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)&DamageEvent;
		if (PointDamageEvent)
		{
			if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("head")) == 0)
			{
				CurrentHP = 0;
				UE_LOG(LogClass, Warning, TEXT("head"));
			}
			else
			{
				CurrentHP -= Damage;
				UE_LOG(LogClass, Warning, TEXT("%s"), *PointDamageEvent->HitInfo.BoneName.ToString());
			}
			CurrentHP = FMath::Clamp<float>(CurrentHP, 0, MaxHP);

			if (CurrentHP == 0)
			{
				SetCurrentState(EEnemyState::Dead);
				
				if (DeathSound)
				{
					UGameplayStatics::PlaySound2D(GetWorld(), DeathSound, 1.f, 1.f, 0.f, nullptr, this);
				}
			}
		}
	}

	return 0.0f;
}


void ASZEnemyBase::SetCurrentState(EEnemyState NewState)
{
	if (CurrentState == EEnemyState::Dead && NewState != EEnemyState::Dead)
	{
		return;
	}

	CurrentState = NewState;

	if (NewState == EEnemyState::Battle)
	{
		if (AttackSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), AttackSound, 1.f, 1.f, 0.f, nullptr, this);
		}
	}
	if (NewState == EEnemyState::Dead)
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PawnSensing->SetSensingUpdatesEnabled(false);
	}

	ASZAIController* AIC = Cast<ASZAIController>(GetController());
	if (AIC)
	{
		AIC->SetCurrentState(CurrentState);
	}
}


void ASZEnemyBase::SetWalkSpeed(float Speed)
{
	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void ASZEnemyBase::SetEnemyMaxHealth(float Health)
{
	CurrentHP= MaxHP = Health;
}
