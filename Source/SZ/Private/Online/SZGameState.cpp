// Fill out your copyright notice in the Description page of Project Settings.


#include "SZGameState.h"
#include "SZGameInstance.h"
#include "SZPlayerState.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "SZWidgetActor.h"
#include "Components/WidgetComponent.h"


ASZGameState::ASZGameState()
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentWidget = nullptr;
	CurrentMatchState = EMatchState::ENotConnected;
}

void ASZGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASZGameState, CurrentMatchState);
	DOREPLIFETIME(ASZGameState, TotalMatchTime);
	DOREPLIFETIME(ASZGameState, Winner);
	DOREPLIFETIME(ASZGameState, TimeStart);
	//DOREPLIFETIME(ASZGameState, CurrentWidgetActor);
}

void ASZGameState::ChangeState_Implementation(EMatchState newState)
{
	if (CurrentMatchState != newState) 
	{
		LeaveState();
		EnterState(newState);
	}
}


void ASZGameState::SetWinner_Implementation(APlayerState* NewWinner)
{
	if (Role = ROLE_Authority)
	{
		Winner = NewWinner;
	}
}

bool ASZGameState::SetWinner_Validate(APlayerState* NewWinner)
{
	return true;
}

EMatchState ASZGameState::GetMatchState()
{
	return CurrentMatchState;
}

void ASZGameState::UpdateStartTime_Implementation(float NewTime)
{
	TimeStart = NewTime;
}

bool ASZGameState::UpdateStartTime_Validate(float NewTime)
{
	return true;
}
void ASZGameState::UpdateMatchTime_Implementation(float NewTime)
{
	TotalMatchTime = NewTime;
}

bool ASZGameState::UpdateMatchTime_Validate(float NewTIme)
{
	return true;
}


void ASZGameState::EnterState(EMatchState newState)
{
	CurrentMatchState = newState;

	//Change state on player
	ASZPlayerState* CurrentPlayerState = Cast<ASZPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	if (CurrentPlayerState)
	{
		CurrentPlayerState->CurrentLocalMatchState = CurrentMatchState;
	}

	//switch on new state
	switch (CurrentMatchState)
	{
	case EMatchState::ENotConnected:
	{
		break;
	}
	case EMatchState::EWaitingForPlayers:
	{
		if (Role < ROLE_Authority)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Instigator = nullptr;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnInfo.OverrideLevel = nullptr;
			UWorld* World = GetWorld();
			CurrentWidgetActor = World->SpawnActor<ASZWidgetActor>(SpawnInfo);
		}

		if (CurrentWidgetActor)
		{
			CurrentWidgetActor->WidgetComponent->SetWidgetClass(cWaitingForPlayers);
			CurrentWidgetActor->WidgetComponent->SetWorldLocationAndRotation(FVector(-840, 545, 1120), FRotator(0, -180, 0));
			CurrentWidgetActor->WidgetComponent->SetDrawSize(FVector2D(1920, 1080));
		}
		//Show waiting for players UI
		//CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), cWaitingForPlayers);
		//CurrentWidget->AddToViewport();

		//change input mode
		USZGameInstance* GameInstance = Cast<USZGameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance)
		{
			GameInstance->SetInputMode(EInputMode::EUIAndGame, true);
		}

		if (Role == ROLE_Authority)
		{
			//set in progress session setting to false
			FBlueprintSessionSetting NewSetting;
			NewSetting.key = FString("InProgress");
			NewSetting.value = FString("false");

			GameInstance->SetOrUpdateSessionSpecialSettingString(NewSetting);
		}
		break;
	}
	case EMatchState::EStartingGame:
	{
		if (Role == ROLE_Authority)
		{
			//respawn all conneted players if we're the server
			for (auto &player : PlayerArray)
			{
				//destroy the current pawn
				player->GetNetOwningPlayer()->PlayerController->GetPawn()->Destroy();
				//spawn the new pawn
				player->GetNetOwningPlayer()->PlayerController->ServerRestartPlayer();
			}
			ChangeState(EMatchState::EGameInProgress);
		}
		break;
	}
	case EMatchState::EGameInProgress:
	{/*
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Instigator = nullptr;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.OverrideLevel = nullptr;
		UWorld* World = GetWorld();
		CurrentProgressWidget = World->SpawnActor<ASZInProgressWidget>(SpawnInfo);
*/
		USZGameInstance* GameInstance = Cast<USZGameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance)
		{
			if (CurrentWidgetActor)
			{
				CurrentWidgetActor->WidgetComponent->SetWidgetClass(cGameInProgress);
				CurrentWidgetActor->WidgetComponent->SetWorldLocationAndRotation(FVector(-840, 545, 1120), FRotator(0, -180, 0));
				CurrentWidgetActor->WidgetComponent->SetDrawSize(FVector2D(1920, 1080));
			}
			//CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), cGameInProgress);
			//CurrentWidget->AddToViewport();

			//if (CurrentProgressWidget)
			//{
			//	/*FTransform PlayerTrasform;

			//	for (auto &player : PlayerArray)
			//	{
			//		PlayerTrasform = player->GetNetOwningPlayer()->PlayerController->GetPawn()->GetTransform();
			//	}*/
			//	CurrentProgressWidget->SetOwner();
			//	CurrentProgressWidget->WidgetComponent->SetWidgetClass(cPlayerHealthInfo);
			//	CurrentProgressWidget->WidgetComponent->SetWorldLocationAndRotation(
			//		FVector(0,0,0), FRotator(0,0,0));
			//	CurrentProgressWidget->WidgetComponent->SetDrawSize(FVector2D(1920, 1080));
			//}
			GameInstance->SetInputMode(EInputMode::EUIAndGame, false);
		}


		if (Role == ROLE_Authority)
		{
			//set in progress session setting to true
			FBlueprintSessionSetting NewSetting;
			NewSetting.key = FString("InProgress");
			NewSetting.value = FString("true");

			GameInstance->SetOrUpdateSessionSpecialSettingString(NewSetting);
		}
		break;
	}
	case EMatchState::EGameComplete:
	{
		USZGameInstance* GameInstance = Cast<USZGameInstance>(GetWorld()->GetGameInstance());

		if (Role == ROLE_Authority)
		{
			for (auto &player : PlayerArray)
			{
				APlayerController* PC = player->GetNetOwningPlayer()->PlayerController;

				PC->GetPawn()->Destroy();
				PC->ServerRestartPlayer();
			}
		}

		CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), cGameComplete);
		//CurrentWidget->AddToViewport();
		GameInstance->SetInputMode(EInputMode::EUIOnly, true);
		break;
	}
	case EMatchState::ERestartingGame:
	{
		USZGameInstance* GameInstance = Cast<USZGameInstance>(GetWorld()->GetGameInstance());

		if (GameInstance)
		{
			if (CurrentWidgetActor)
			{
				CurrentWidgetActor->WidgetComponent->SetWidgetClass(cChangingLevel);
				CurrentWidgetActor->WidgetComponent->SetWorldLocationAndRotation(FVector(-840, 545, 1120), FRotator(0, -180, 0));
				CurrentWidgetActor->WidgetComponent->SetDrawSize(FVector2D(1920, 1080));
			}
			//CurrentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), cChangingLevel);
			//CurrentWidget->AddToViewport();

			GameInstance->SetInputMode(EInputMode::EUIOnly, true);
		}

		if (Role == ROLE_Authority)
		{
			Winner = nullptr;
			//respawn all conneted players if we're the server
			for (auto &player : PlayerArray)
			{
				//destroy the current pawn
				player->GetNetOwningPlayer()->PlayerController->GetPawn()->Destroy();
				//spawn the new pawn
				player->GetNetOwningPlayer()->PlayerController->ServerRestartPlayer();
			}

			//Travel to a new instance of our map by getting the session setting.
			//"MAPNAME" and passing it to ServerTravel
			FString mapname = GameInstance->GetSessionSpecialSettingString("MAPNAME");
			GetWorld()->ServerTravel(mapname);
		}
		break;
	}
	}
}

void ASZGameState::LeaveState()
{
	//switch on new state
	switch (CurrentMatchState)
	{
	case EMatchState::ENotConnected:
	{
		//		break;
	}
	case EMatchState::EWaitingForPlayers:
	{
		//		break;
	}
	case EMatchState::EStartingGame:
	{
		//		break;
	}
	case EMatchState::EGameInProgress:
	{
		//		break;
	}
	case EMatchState::EGameComplete:
	{
		//		break;
	}
	case EMatchState::ERestartingGame:
	{
		//hide any widget
		if (CurrentWidget) {
			//CurrentWidget->RemoveFromViewport();
			CurrentWidget = nullptr;
		}
		break;
	}
	}
}
void ASZGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ensure we're not out of sync with server
	//get player state
	ASZPlayerState* PlayerState = Cast<ASZPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);

	if (PlayerState)
	{
		//if we're out of sync
		if (PlayerState->CurrentLocalMatchState != CurrentMatchState)
		{
			LeaveState();
			EnterState(CurrentMatchState);
		}
	}

	/*switch (CurrentMatchState)
	{
		case EMatchState::EGameInProgress:
		{
			if(CurrentProgressWidget)
			{
				CurrentProgressWidget->WidgetComponent->SetWorldLocationAndRotation(
					PlayerState->GetLocalPlayerTransform().GetLocation(), PlayerState->GetLocalPlayerTransform().GetRotation());
			}
		}
		break;
	}*/
}