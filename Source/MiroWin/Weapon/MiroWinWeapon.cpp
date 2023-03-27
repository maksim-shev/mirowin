// Fill out your copyright notice in the Description page of Project Settings.


#include "MiroWin/Weapon/MiroWinWeapon.h"

#include "MiroWin/UI/MiroWinWeaponWidget.h"

void UMiroWinWeapon::Init(AMiroWinCharacter* _pOwner)
{
	if (!WeaponWidgetClass)
	{
		return;
	}

	UWorld* pWorld = UObject::GetWorld();
	if (!IsValid(pWorld))
	{
		return;
	}

	WeaponWidget = CreateWidget<UMiroWinWeaponWidget>(pWorld, WeaponWidgetClass);
	if (IsValid(WeaponWidget))
	{
		WeaponWidget->Init(this);
	}

	OwnerPawn = _pOwner;
}

void UMiroWinWeapon::AddAmmo(int32 _Amount)
{
	Ammo = FMath::Clamp(Ammo + _Amount, 0, MaxAmmo);
	AmmoAmountChangedDelegate.Broadcast(Ammo);
}