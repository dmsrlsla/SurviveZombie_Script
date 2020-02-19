// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SZGameState.h"
#include "SZPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SZ_API ASZPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASZPlayerState();


	/** get current team */
	int32 GetTeamNum() const;


	/** replicate team colors. Updated the players mesh colors appropriately */
	UFUNCTION()
	void OnRep_TeamColor();

	UFUNCTION(BlueprintCallable, Category = "Player State")
		void CollectCoin();
	UFUNCTION(BlueprintCallable, Category = "Player State")
		void CollectHeart();

	UFUNCTION(BlueprintCallable, Category = "Player State")
		void ReceiveDamage(int amount);

	//For keeping track of what UI we're displaying locally
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		EMatchState CurrentLocalMatchState;

	//boolean for keeping track of ready state
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		bool bIsReady;

	//boolean for keeping track of whether a player wants to specate
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		bool bSpectator;

	//int for keeping track of selected character
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		int SelectedCharacterIndex;

	//we'll also need server functions for changing these
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "SZ Player State")
		void ToggleReady();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "SZ Player State")
		void ToggleSpectator();
	
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "SZ Player State")
		void SelectCharacter(int index);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "SZ Player State")
		void PlayerRespawnedAfterDeath();

	int GetCurrentHealth();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		int CurrentHealth;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		int NumberOfDeaths;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		int MaxHealth;

	void SetMaxHealthFromCharacter(int MX) { MaxHealth = MX; }
	void SetCurrentHealthFromCharacter(int Health) {CurrentHealth = Health; }

	//FTransform GetLocalPlayerTransform();
protected:
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "SZ Player State")
		int NumberOfCoinCollected;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_TeamColor)
	int32 TeamNumber;

	/** Set the mesh colors based on the current teamnum variable */
	void UpdateTeamColors();

};
