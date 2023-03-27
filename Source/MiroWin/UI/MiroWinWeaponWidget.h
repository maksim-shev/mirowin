// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiroWinWeaponWidget.generated.h"

class UMiroWinWeapon;
class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class MIROWIN_API UMiroWinWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UMiroWinWeapon* _Weapon);

private:
	UPROPERTY(meta=(BindWidget))
	UImage* WeaponIcon = nullptr;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmmoCount = nullptr;

	UPROPERTY()
	UMiroWinWeapon* Weapon;

	UFUNCTION()
	void UpdateAmmoCount(int32 _AmmoCount);
};