#include "SZStyle.h"
#include "SlateGameResources.h"
#include "SZ.h"

TSharedPtr<FSlateStyleSet> FSZStyle::SZStyleInstance = NULL;

void FSZStyle::Initialize()
{
	if (!SZStyleInstance.IsValid())
	{
		SZStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*SZStyleInstance);
	}
}

void FSZStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SZStyleInstance);
	ensure(SZStyleInstance.IsUnique());
	SZStyleInstance.Reset();
}

FName FSZStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SZStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH(RelativePath,...) FSlateImageBrush(FPaths::ProjectContentDir() / "Slate" / RelativePath + TEXT(".png"), __VA_ARGS__)
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".png"), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".ttf"), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FPaths::ProjectContentDir() / "Slate"/ RelativePath + TEXT(".otf"), __VA_ARGS__ )

PRAGMA_DISABLE_OPTIMIZATION
TSharedRef<class FSlateStyleSet> FSZStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(FSZStyle::GetStyleSetName(), "/Game/UI/Styles", "/Game/UI/Styles");
	FSlateStyleSet& Style = StyleRef.Get();

	Style.Set("SZGame.Speaker", new IMAGE_BRUSH("Images/SoundCue_SpeakerIcon", FVector2D(32, 32)));

	// The border image used to draw the replay timeline bar
	Style.Set("SZGame.ReplayTimelineBorder", new BOX_BRUSH("Images/ReplayTimeline", FMargin(3.0f / 8.0f)));

	// The border image used to draw the replay timeline bar
	Style.Set("SZGame.ReplayTimelineIndicator", new IMAGE_BRUSH("Images/ReplayTimelineIndicator", FVector2D(4.0f, 26.0f)));

	// The image used to draw the replay pause button
	Style.Set("SZGame.ReplayPauseIcon", new IMAGE_BRUSH("Images/ReplayPause", FVector2D(32.0f, 32.0f)));

	Style.Set("SZGame.MenuServerListTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 14))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.MenuStoreListTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 14))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.ScoreboardListTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 14))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.MenuProfileNameStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 18))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.MenuTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 20))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.MenuHeaderTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 26))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.WelcomeScreen.WelcomeTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Medium", 32))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.DefaultScoreboard.Row.HeaderTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 24))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(0, 1))
	);

	Style.Set("SZGame.DefaultScoreboard.Row.StatTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 18))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FVector2D(0, 1))
	);

	Style.Set("SZGame.SplitScreenLobby.StartMatchTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Regular", 16))
		.SetColorAndOpacity(FLinearColor::Green)
		.SetShadowOffset(FVector2D(0, 1))
	);

	Style.Set("SZGame.DemoListCheckboxTextStyle", FTextBlockStyle()
		.SetFont(TTF_FONT("Fonts/Roboto-Black", 12))
		.SetColorAndOpacity(FLinearColor::White)
		.SetShadowOffset(FIntPoint(-1, 1))
	);

	Style.Set("SZGame.Switch.Left", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonLeft", FVector2D(32, 32)))
	);

	Style.Set("SZGame.Switch.Right", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonRight", FVector2D(32, 32)))
	);

	Style.Set("SZGame.Switch.Up", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonUp", FVector2D(32, 32)))
	);

	Style.Set("SZGame.Switch.Down", FInlineTextImageStyle()
		.SetImage(IMAGE_BRUSH("Images/SwitchButtonDown", FVector2D(32, 32)))
	);

	return StyleRef;
}
PRAGMA_ENABLE_OPTIMIZATION

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FSZStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle & FSZStyle::Get()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return *SZStyleInstance;
}
