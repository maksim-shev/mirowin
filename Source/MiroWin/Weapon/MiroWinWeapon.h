// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiroWinWeapon.generated.h"

class AMiroWinCharacter;
class UWidget;
// Enum for all weapon types. Has a direct correspondence with UMiroWinWeapon subclasses (see AMiroWinCharacter::AllWeapons)
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Undefined,
	SemiAutoRifle,
	AutoRifle,
	MAX_VALUE
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoAmountChanged, int32, _AmmoCount);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class MIROWIN_API UMiroWinWeapon : public UObject
{
	GENERATED_BODY()

public:
	void Init(AMiroWinCharacter* _pOwner);

	virtual void PullTrigger(){}

	UFUNCTION(BlueprintCallable)
	virtual void ReleaseTrigger(){}

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AddAmmo(int32 _Amount);

	UFUNCTION(BlueprintGetter, Category="Weapon")
	int32 GetMaxAmmo() const { return MaxAmmo; }

	UFUNCTION(BlueprintGetter, Category="Weapon")
	int32 GetAmmo() const { return Ammo; }

	UPROPERTY(BlueprintAssignable, Category="Weapon")
	FOnAmmoAmountChanged AmmoAmountChangedDelegate;

	UFUNCTION(BlueprintGetter, Category="Weapon")
	UMiroWinWeaponWidget* GetWeaponWidget() const { return WeaponWidget; }

	UFUNCTION(BlueprintSetter, Category="Weapon")
	void SetWeaponWidget(UMiroWinWeaponWidget* _WeaponWidget) { WeaponWidget = _WeaponWidget; }

	UFUNCTION(BlueprintGetter, Category="Weapon")
	EWeaponType GetType() const { return Type; }

	UFUNCTION()
	UTexture2D* GetWeaponIcon() const { return WeaponIcon; }

protected:
	UPROPERTY()
	AMiroWinCharacter* OwnerPawn = nullptr;

private:
	UPROPERTY(BlueprintGetter=GetMaxAmmo, EditDefaultsOnly, Category="Weapon")
	int32 MaxAmmo = 100;

	UPROPERTY(BlueprintGetter=GetAmmo, EditDefaultsOnly, Category="Weapon")
	int32 Ammo = 0;

	UPROPERTY(BlueprintGetter=GetType, Category="Weapon")
	EWeaponType Type;

	UPROPERTY(BlueprintGetter=GetWeaponWidget, BlueprintSetter=SetWeaponWidget, Category="Weapon")
	UMiroWinWeaponWidget* WeaponWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UMiroWinWeaponWidget> WeaponWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	UTexture2D* WeaponIcon = nullptr;
};