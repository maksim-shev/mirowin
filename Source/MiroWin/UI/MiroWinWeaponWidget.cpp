// Fill out your copyright notice in the Description page of Project Settings.


#include "MiroWin/UI/MiroWinWeaponWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MiroWin/Weapon/MiroWinWeapon.h"

void UMiroWinWeaponWidget::Init(UMiroWinWeapon* _Weapon)
{
	if (!IsValid(_Weapon))
	{
		return;
	}

	Weapon = _Weapon;
	Weapon->AmmoAmountChangedDelegate.AddDynamic(this, &UMiroWinWeaponWidget::UpdateAmmoCount);
	UTexture2D* pWeaponIcon = Weapon->GetWeaponIcon();
	if (IsValid(pWeaponIcon))
	{
		WeaponIcon->SetBrushFromTexture(pWeaponIcon);
	}

	UpdateAmmoCount(Weapon->GetAmmo());
}

void UMiroWinWeaponWidget::UpdateAmmoCount(int32 _AmmoCount)
{
	if (IsValid(AmmoCount))
	{
		AmmoCount->SetText(FText::AsNumber(_AmmoCount));
	}
}