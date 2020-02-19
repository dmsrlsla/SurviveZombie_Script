// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_CheckAttackOverlap.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SZCharacter.h"
#include "Enemy/SZEnemyBase.h"

void UAnimNotify_CheckAttackOverlap::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(MeshComp->GetOwner());

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(MyZombie);
	TArray<AActor*> OutActors;

	if (MyZombie)
	{
		bool Result = UKismetSystemLibrary::SphereOverlapActors(MyZombie->GetWorld(),
			MyZombie->GetActorLocation(),
			200.0f,
			ObjectTypes,
			ASZCharacter::StaticClass(),
			IgnoreActors,
			OutActors);

		if (Result) //누군가 맞았다.
		{
			UGameplayStatics::ApplyDamage(OutActors[0],
				MyZombie->AttackDamage,
				MyZombie->GetController(),
				MyZombie,
				nullptr);
		}

	}
}
