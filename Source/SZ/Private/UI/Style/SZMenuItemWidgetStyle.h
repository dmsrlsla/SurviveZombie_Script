#pragma once
#include "SlateWidgetStyleContainerBase.h"
#include "Styling/SlateBrush.h"
#include "SZMenuItemWidgetStyle.generated.h"

USTRUCT()
struct FSZMenuItemStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSZMenuItemStyle();
	virtual ~FSZMenuItemStyle();

	//FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSZMenuItemStyle& GetDefault();

	/* Brush used for the item background */
	UPROPERTY(EditAnywhere, Category = "Appearance")
		FSlateBrush BackgroundBrush;
	FSZMenuItemStyle& SetBackgroundBrush(const FSlateBrush& InBackgroundBrush) { BackgroundBrush = InBackgroundBrush; return *this; }

	/* Image used for the left arrow */
	UPROPERTY(EditAnywhere, Category = "Appearance")
		FSlateBrush LeftArrowImage;
	FSZMenuItemStyle& SetLeftArrowImage(const FSlateBrush& InLeftArrowImage) { LeftArrowImage = InLeftArrowImage; return *this; }
	UPROPERTY(EditAnywhere, Category = "Appearance")
		FSlateBrush RightArrowImage;
	FSZMenuItemStyle& SetRightArrowImage(const FSlateBrush& InRightArrowImage) { RightArrowImage = InRightArrowImage; return *this; }
};

UCLASS(hidecategories = Object, MinimalAPI)
class USZMenuItemWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	/* the actual data describing the menu's appearance */
	UPROPERTY(Category = "Appearance", EditAnywhere, meta = (ShowOnlyInnerProperties))
		FSZMenuItemStyle MenuItemStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MenuItemStyle);
	}
};