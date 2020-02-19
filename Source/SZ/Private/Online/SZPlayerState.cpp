// Fill out your copyright notice in the Description page of Project Settings.


#include "SZPlayerState.h"
#include "UnrealNetwork.h"
#include "SZCharacter.h"

ASZPlayerState::ASZPlayerState()
{
	NumberOfCoinCollected = 0;
	MaxHealth = 3;
	CurrentHealth = MaxHealth;
	NumberOfDeaths = 0;

	bIsReady = false;
	bSpectator = false;
	SelectedCharacterIndex = 0;
}

/*
UPROPERTY에 Replicated매크로를 추가하는 것만으로는 적절하게 레플리케이트되었다고 할 수 없다.
프로퍼티 레플리케이션을 완성하기 위해서는,
GetLifetimeREplicatedProps함수를 구현해야한다.
이를 위해, UnrealNetwork.h파일을 인클루드 해야한다.
*/
void ASZPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASZPlayerState, CurrentHealth);
	DOREPLIFETIME(ASZPlayerState, NumberOfCoinCollected);
	DOREPLIFETIME(ASZPlayerState, NumberOfDeaths);
	DOREPLIFETIME(ASZPlayerState, bIsReady);
	DOREPLIFETIME(ASZPlayerState, bSpectator);
	DOREPLIFETIME(ASZPlayerState, SelectedCharacterIndex);
	DOREPLIFETIME(ASZPlayerState, TeamNumber);
}

void ASZPlayerState::ToggleReady_Implementation()
{
	bIsReady = !bIsReady;
}

bool ASZPlayerState::ToggleReady_Validate()
{
	return true;
}

void ASZPlayerState::ToggleSpectator_Implementation()
{
	bSpectator = !bSpectator;
}

bool ASZPlayerState::ToggleSpectator_Validate()
{
	return true;
}

void ASZPlayerState::SelectCharacter_Implementation(int index)
{
	SelectedCharacterIndex = index;
}

bool ASZPlayerState::SelectCharacter_Validate(int index)
{
	return true;
}


int ASZPlayerState::GetCurrentHealth()
{
	return CurrentHealth;
}

void ASZPlayerState::UpdateTeamColors()
{
	AController* OwnerController = Cast<AController>(GetOwner());
	if (OwnerController != NULL)
	{
		ASZCharacter* MyCharacter = Cast<ASZCharacter>(OwnerController->GetCharacter());
		if (MyCharacter != NULL)
		{
			//MyCharacter->UpdateTeamColorsAllMIDs();
		}
	}
}



int32 ASZPlayerState::GetTeamNum() const
{
	return TeamNumber;
}

void ASZPlayerState::PlayerRespawnedAfterDeath_Implementation()
{
	if (Role == ROLE_Authority)
	{
		CurrentHealth = MaxHealth;

		//NumberOfCoinCollected = NumberOfCoinCollected / 2;
		NumberOfDeaths++;
	}
}

bool ASZPlayerState::PlayerRespawnedAfterDeath_Validate()
{
	return true;
}
void  ASZPlayerState::ReceiveDamage(int amount)
{
	CurrentHealth -= amount;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void ASZPlayerState::OnRep_TeamColor()
{
	UpdateTeamColors();
}

void ASZPlayerState::CollectCoin()
{
	NumberOfCoinCollected += 1;
}

void ASZPlayerState::CollectHeart()
{
	CurrentHealth += 1;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}