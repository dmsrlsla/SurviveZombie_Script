// Fill out your copyright notice in the Description page of Project Settings.


#include "SZGameMode.h"
#include "SZCharacter.h"
#include "UI/SZHUD.h"
#include "SZPlayerState.h"
#include "SZAIController.h"
#include "SZPlayerController.h"
#include "SZEnemyBase.h"
#include "SZGameInstance.h"
#include "SZGameState.h"
#include "MainMenuPawn.h"
#include "SZWidgetActor.h"

ASZGameMode::ASZGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	/*
	현재 월드의 모든 PC를 찾는법
	for (auto iter = GetWorld()->GetPlayerControllerIterator(); iter; ++iter)
	{

	}*/
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("/Game/Blueprints/Pawns/PlayerPawn"));
	//DefaultPawnClass = PlayerPawnOb.Class;

	static ConstructorHelpers::FClassFinder<APawn> EnemyPawnOb(TEXT("/Game/WorkSpace/PARKJUNHONG/BP_EnemyPawn"));
	EnemyPawnClass = EnemyPawnOb.Class;

	HUDClass = ASZHUD::StaticClass();
	DefaultPawnClass = ASZCharacter::StaticClass();
	PlayerControllerClass = ASZPlayerController::StaticClass();
	PlayerStateClass = ASZPlayerState::StaticClass();
	
	//SpectatorClass = AShooterSpectatorPawn::StaticClass();
	//GameStateClass = ASZGA::StaticClass();
	//ReplaySpectatorPlayerControllerClass = AShooterDemoSpectator::StaticClass();

	MinRespawnDelay = 5.0f;

	//bAllowBots = true;
	//bNeedsBotCreation = true;
	//bUseSeamlessTravel = true;

	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	TimeSinceStart = 0.0f;
	TimeProgressStart = 30.0f;
}

bool ASZGameMode::CanDealDamage(ASZPlayerState * DamageInstigator, ASZPlayerState * DamagedPlayer) const
{
	return true;
}

void ASZGameMode::Logout(AController* exiting)
{
	Super::Logout(exiting);

	ASZGameState* SZGameState = Cast<ASZGameState>(GameState);

	if (SZGameState)
	{
		//remove the player state from the lists of player;
		SZGameState->RemovePlayerState(exiting->PlayerState);
	}
}

void ASZGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ensure we're on server
	if (Role == ROLE_Authority)
	{
		//get current game state
		ASZGameState* SZGameState = Cast<ASZGameState>(GameState);

		//get game instance
		USZGameInstance* GameInstance = Cast<USZGameInstance>(GetGameInstance());

		if (GameInstance && SZGameState)
		{
			//check we're in game
			if (GameInstance->GetGameState() == EGameState::EMultiplayerInGame)
			{
				//check match state
				switch (SZGameState->GetMatchState())
				{
				case EMatchState::ENotConnected:
				{
					SZGameState->SetWidgetActor(GameInstance->CurrentWidgetActor);
					SZGameState->ChangeState(EMatchState::EWaitingForPlayers);
					break;
				}
				case EMatchState::EWaitingForPlayers:
				{
					if (TimeProgressStart >= 0.0f)
					{
						TimeProgressStart -= DeltaTime;
						SZGameState->UpdateStartTime(TimeProgressStart);
					}
					
					//ASZGameState* const SZGameState = Cast<ASZGameState>(GameState);

					/*현재 플레이어의 수*/
					TArray<APlayerState*> PlayerNum = SZGameState->PlayerArray;

					/*int MaxNumOfAIPawn;

					for (int CurrentPlayer = PlayerNum, CurrentPlayer < MaxNumOfAIPawn; CurrentPlayer++)
					{

					}*/
					break;
				}
				case EMatchState::EGameInProgress:
				{
					TimeSinceStart += DeltaTime;
				
					for (auto &Player : SZGameState->PlayerArray)
					{
						ASZPlayerState* SZPlayer = Cast<ASZPlayerState>(Player);

						if (SZPlayer && !SZPlayer->bSpectator)
						{
							if (SZPlayer->GetCurrentHealth() <= 0)
							{
								APlayerController* PlayerController = SZPlayer->GetNetOwningPlayer()->PlayerController;

								SZPlayer->PlayerRespawnedAfterDeath();

								PlayerController->GetPawn()->Destroy();
								PlayerController->ServerRestartPlayer();
							}
						}
					}
					SZGameState->UpdateMatchTime(TimeSinceStart);

					break;
				}
				case EMatchState::EGameComplete:
				{
					break;
				}
				default:
				{
					//any other match state will reset timesince start to 0
					if (TimeSinceStart != 0.0f)
					{
						TimeSinceStart = 0.0f;
						SZGameState->UpdateMatchTime(TimeSinceStart);
					}
				}
				}
			}
		}
	}
}

/*위젯은 Replicate가 안되므로 서버에서 생성하는거 삭제 */
void ASZGameMode::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();

	USZGameInstance* GameInstance = Cast<USZGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		//CreateMainMenuPawn();
		GameInstance->CurrentWidgetActor = CreateWidgetActor();
	}
}
/* Accept or reject a player attempting to join the server*/
//void ASZGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
//{
//	Super::PreLogin(Options,Address,UniqueId,ErrorMessage);
//}

/* Starts Match Warmup*/
 void ASZGameMode::PostLogin(APlayerController* NewPlayer)
 {
	 Super::PostLogin(NewPlayer);

	 ASZPlayerController* NewPC = Cast<ASZPlayerController>(NewPlayer);

	 ASZGameState* SZGameState = Cast<ASZGameState>(GameState);
	 USZGameInstance* GameInstance = Cast<USZGameInstance>(GetGameInstance());

	// GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("NewPlayer Loged in"));

	 //NewPC->UnPossess();
	 //NewPC->Possess(SZGameState->Pawns.PawnClass);

	 if (SZGameState && GameInstance)
	 {
		 if (NewPC && SZGameState->GetMatchState() == EMatchState::EGameInProgress)
		 {
			// UE_LOG(LogTemp, Warning, TEXT("NewPlayer Loged in while playing Game"));

			// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), 123.0f));
			 GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("NewPlayer Loged in While playing game")); // 화면출력
		 }
	 }
}
float ASZGameMode::ModifyDamage(float Damage, AActor * DamagedActor, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) const
{
	float ActualDamage = Damage;

	//@ Todo:: prevent Teamkill
	//if (DamagedPawn  && EventInstigator)
	//{
	//	ASZ
	//}

	return ActualDamage;
}

//AMainMenuPawn* ASZGameMode::CreateMainMenuPawn()
//{
//	FActorSpawnParameters SpawnInfo;
//	SpawnInfo.Instigator = nullptr;
//	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	SpawnInfo.OverrideLevel = nullptr;
//
//	UWorld* World = GetWorld();
//
//	ASZGameState* SZGameState = Cast<ASZGameState>(GameState);
//
//	SZGameState->Pawns.PawnClass = World->SpawnActor<AMainMenuPawn>(SpawnInfo);
//	return SZGameState->Pawns.PawnClass;
//}

ASZCharacter* ASZGameMode::CreatePlayerAIPawn()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = nullptr;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = nullptr;

	UWorld* World = GetWorld();

	ASZCharacter* ACharacter = World->SpawnActor<ASZCharacter>(SpawnInfo);

	return ACharacter;
}

//void ASZGameMode::HandleStartingNewPlayer_Implementation(APlayerController * NewPlayer)
//{
//
//}

ASZWidgetActor* ASZGameMode::CreateWidgetActor()
{
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.Instigator = nullptr;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = nullptr;

	UWorld* World = GetWorld();

	if (AWA == nullptr)
	{
		AWA = World->SpawnActor<ASZWidgetActor>(SpawnInfo);

		return AWA;
	}

	else
	{
		return AWA;
	}
}


UClass* ASZGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	ASZGameState* SZGameState = Cast<ASZGameState>(GameState);
	USZGameInstance* GameInstance = Cast<USZGameInstance>(GetGameInstance());

	if (SZGameState && GameInstance)
	{
		/*if (GameInstance->GetGameState() == EGameState::EMainMenu)
		{
			return SZGameState->Pawns.PawnClass;
		}*/
		//check whether we're in game
		if (GameInstance->GetGameState() == EGameState::EMultiplayerInGame)
		{
			//check whether the game is in progress or is starting
			if (SZGameState->GetMatchState() == EMatchState::EGameInProgress ||
				SZGameState->GetMatchState() == EMatchState::EStartingGame)
			{
				ASZPlayerState* PlayerState = Cast<ASZPlayerState>(InController->PlayerState);
			
				if (PlayerState)
				{
					//check if we're a spectator or that the player is not ready, meaning they joined after the game had started
					if (PlayerState->bSpectator || !PlayerState->bIsReady)
					{
						//return spectator class;

						//return ASpectatorPawn::StaticClass(); GameStateBase에 있어 주석
						return SZGameState->Characters[0].CharacterClass;
					}

					//otherwise we return the selected character
					int SelectedCharacter = PlayerState->SelectedCharacterIndex;

					//if it is a valid index, return that class
					if (SZGameState->Characters.IsValidIndex(SelectedCharacter))
					{
						return SZGameState->Characters[SelectedCharacter].CharacterClass;
					}
					else
					{
						//if the index is invalid, return the first character in the list.
						return SZGameState->Characters[0].CharacterClass;
					}
				}
			}
		}
	}
	//if the match isnt starting and isnt in progress, we default to spectator
	//return ASpectatorPawn::StaticClass();
	//return SZGameState->Characters[0].CharacterClass;
	return SZGameState->Pawns.PawnClass;

}