
#include "AnimNotifyState_EnemyWalkSpeed.h"
#include "Enemy/SZEnemyBase.h"
#include "Components/SkeletalMeshComponent.h"

void UAnimNotifyState_EnemyWalkSpeed::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(MeshComp->GetOwner());
	if (MyZombie)
	{
		MyZombie->SetWalkSpeed(1.0f);
	}
}

void UAnimNotifyState_EnemyWalkSpeed::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_EnemyWalkSpeed::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ASZEnemyBase* MyZombie = Cast<ASZEnemyBase>(MeshComp->GetOwner());
	if (MyZombie)
	{
		MyZombie->SetWalkSpeed(MyZombie->WalkSpeed);
	}
}
