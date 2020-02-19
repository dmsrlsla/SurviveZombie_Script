// Fill out your copyright notice in the Description page of Project Settings.


#include "SZInventorySlotWidget.h"
#include "SZWeaponBase.h"

void USZInventorySlotWidget::SetEquippedItem()
{
}

void USZInventorySlotWidget::SetItemTexture(AActor * Item)
{
	//if (Item)
	//{
	//	// 좀 생각해보겠음.
	//	ASZWeaponBase* Weapon = Cast<ASZWeaponBase>(Item);
	//	if (Weapon)
	//	{
	//		ItemTexture = Weapon->GetPickupTexture();
	//	}
	//}
	//else
	//{
	//	ItemTexture = nullptr;
	//}
}

void USZInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
