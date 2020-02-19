// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "Online.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "EngineMinimal.h"
#include "SZGameMode.h"
#include "SZGameState.h"
#include "SZCharacter.h"
#include "SZPlayerController.h"
#include "Engine/EngineTypes.h"

class UBehaviorTreeComponent;

#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2