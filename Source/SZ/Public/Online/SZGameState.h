// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SZGameState.generated.h"


/* ENUM FOR DEFINING MATCH STATE */
UENUM(BlueprintType)
enum class EMatchState : uint8
{
	ENotConnected				UMETA(DisplayName = "Not Connected"),
	EWaitingForPlayers			UMETA(DisplayName = "Waiting For Players"),
	EStartingGame				UMETA(DisplayName = "Starting Game"),
	EGameInProgress				UMETA(DisplayName = "Game In Progress"),
	EGameComplete				UMETA(DisplayName = "Game Complete"),
	ERestartingGame				UMETA(DisplayName = "Restarting Game"),
};

/* STRUCT FOR DEFINING A CHARACTER FOR THE CHARACTER SELECT SCREEN */
USTRUCT(BlueprintType)
struct FCharacterSpecification
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
	TSubclassOf<class ASZCharacter> CharacterClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
	UTexture2D* CharacterIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
	FString CharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
	UTexture2D*	CharacterLiveIcon;
};

USTRUCT(BlueprintType)
struct FPawnSpecification
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main State")
	TSubclassOf<class AMainMenuPawn> PawnClass;
};

USTRUCT(BlueprintType)
struct F3DActorSpecification
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main State")
	TSubclassOf<class ASZWidgetActor> WidgetClass;
};
/**
 * 
 */
UCLASS()
class SZ_API ASZGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASZGameState();
	/* CLASS REFERENCES TO SCREENS TO BE DISPLAYED DURING A MATCH */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
	TSubclassOf<class UUserWidget> cWaitingForPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
		TSubclassOf<class UUserWidget> cGameInProgress;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
		TSubclassOf<class UUserWidget> cChangingLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
		TSubclassOf<class UUserWidget> cGameComplete;


	//Character list we'll specify in the editor:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match State")
		TArray<FCharacterSpecification> Characters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main State")
		FPawnSpecification Pawns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main State")
		F3DActorSpecification Widget;
	//For changing state
	UFUNCTION(NetMulticast, BlueprintCallable, Reliable, Category = "Match State")
	void ChangeState(EMatchState newState);

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly/*, Replicated*/)
	class ASZWidgetActor* CurrentWidgetActor;

	void SetWidgetActor(ASZWidgetActor* WidgetActor) { CurrentWidgetActor = WidgetActor; }
	void SetCurrentWidgetActor(class ASZWidgetActor* Current3DActor) { CurrentWidgetActor = Current3DActor; }
	//get current state
	UFUNCTION(BlueprintCallable, Category = "Match State")
	EMatchState GetMatchState();

	virtual void Tick(float DeltaTime) override;
	

	//Update Match Time
	

	UFUNCTION(Server, Reliable, WithValidation, Category = "Match State")
	void UpdateMatchTime(float NewTime);

	UFUNCTION(Server, Reliable, WithValidation, Category = "Match State")
		void UpdateStartTime(float NewTime);


	UPROPERTY(Replicated, BlueprintReadOnly)
	APlayerState* Winner;

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable, Category = "Match State")
	void SetWinner(APlayerState* NewWinner);
	UFUNCTION(BlueprintCallable)
	void EnterState(EMatchState newState);
private:
	//the currently displayed widget
	UUserWidget* CurrentWidget;
	//the current state, replicated
	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	EMatchState CurrentMatchState;

	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float TotalMatchTime;

	UPROPERTY(Replicated, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	float TimeStart;

	//for changing state

	void LeaveState();
};
