// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/SZHUD.h"
#include "SZ.h"

const float ASZHUD::MinHudScale = 0.5f;

ASZHUD::ASZHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NoAmmoFadeOutTime = 1.f;
	HitNotifyDisplayTime = 0.75f;
	KillFadeOutTime = 2.f;
	LastEnemyHitDisplayTime = 0.2f;
	NoAmmoNotifyTime = -NoAmmoFadeOutTime;
	LastKillTime = -KillFadeOutTime;
	LastEnemyHitTime = -LastEnemyHitDisplayTime;

	static ConstructorHelpers::FObjectFinder<UTexture2D> HitTextureOb(TEXT("/Game/UI/HUD/HitIndicator"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets02TextureOb(TEXT("/Game/UI/HUD/HUDAssets02"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowHealthOverlayTextureOb(TEXT("/Game/UI/HUD/LowHealthOverlay"));

	// Fonts are not included in dedicated server builds.
#if !UE_SERVER
	{
		static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/UI/HUD/Roboto51"));
		static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/UI/HUD/Roboto18"));
		BigFont = BigFontOb.Object;
		NormalFont = NormalFontOb.Object;
	}
#endif //!UE_SERVER

	HitNotifyTexture = HitTextureOb.Object;
	HUDMainTexture = HUDMainTextureOb.Object;
	HUDAssets02Texture = HUDAssets02TextureOb.Object;
	LowHealthOverlayTexture = LowHealthOverlayTextureOb.Object;


}
void ASZHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void ASZHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr)
	{
		return;
	}
	ScaleUI = Canvas->ClipY / 1080.f;

}

void ASZHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}