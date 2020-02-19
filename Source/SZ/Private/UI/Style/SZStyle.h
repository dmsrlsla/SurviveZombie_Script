#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class FSZStyle
{
public:

	static void Initialize();
	static void Shutdown();

	/* Reload Textures used by slate Renderer*/
	static void ReloadTextures();

	/* return The Slate style set for the SZ Game*/
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedRef<class FSlateStyleSet> Create();
private:
	static TSharedPtr<class FSlateStyleSet> SZStyleInstance;
};