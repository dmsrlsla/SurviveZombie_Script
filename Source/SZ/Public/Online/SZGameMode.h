// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SZWidgetActor.h"
#include "Engine/World.h"
#include "SZGameMode.generated.h"

class ASZAIController;
class ASZPlayerState;

UCLASS(config=Game)
class ASZGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	TSubclassOf<APawn> EnemyPawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameMode")
		TSubclassOf<APawn> PlayerPawnClass;

	virtual void Logout(AController* exiting) override;
	virtual void Tick(float DeltaTime) override;

	//for spawning appropriate character
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/** can players damage each other? */
	virtual bool CanDealDamage(ASZPlayerState* DamageInstigator, ASZPlayerState* DamagedPlayer) const;

	/* called before startmatch */
	virtual void HandleMatchIsWaitingToStart() override;

	/* Starts Match Warmup*/
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** prevents friendly fire */
	virtual float ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;

	class ASZWidgetActor* CreateWidgetActor();
	//class AMainMenuPawn* CreateMainMenuPawn();

	
	class ASZCharacter* CreatePlayerAIPawn();

	//Post Login 함수와 같이, 현재 게임에 접속한 PlayerController 받을 수 있다.
	//Post Login같은 경우 Seamless Travel을 하게 될때 맵 이동후 한번더 PC를 호출받을 수 없지만
	//이 함수는 한번 게임에 들어온 PC를 알려주게 된다.
	//이 매개변수의 들어오는 데이터를 배열로 지정하게 되면 
	//현재 게임에 접속한 플레이어의 컨트롤러를 다루기 용이해진다.
	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	float TimeSinceStart;

	float TimeProgressStart;

	class ASZWidgetActor* AWA;
};
