#include "SZMenuItemWidgetStyle.h"

FSZMenuItemStyle::FSZMenuItemStyle()
{
}

FSZMenuItemStyle::~FSZMenuItemStyle()
{
}

const FName FSZMenuItemStyle::TypeName(TEXT("FSZMenuItemStyle"));


const FSZMenuItemStyle & FSZMenuItemStyle::GetDefault()
{
	static FSZMenuItemStyle Default;
	return Default;
}

void FSZMenuItemStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	OutBrushes.Add(&BackgroundBrush);
	OutBrushes.Add(&LeftArrowImage);
	OutBrushes.Add(&RightArrowImage);
}

USZMenuItemWidgetStyle::USZMenuItemWidgetStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
