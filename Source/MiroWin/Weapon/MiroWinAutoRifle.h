// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiroWin/Weapon/MiroWinWeapon.h"
#include "MiroWinAutoRifle.generated.h"

/**
 *
 */
UCLASS()
class MIROWIN_API UMiroWinAutoRifle : public UMiroWinWeapon
{
	GENERATED_BODY()

	virtual void PullTrigger() override;
	virtual void ReleaseTrigger() override;
	void Shoot();

	FTimerHandle ShootTimerHandle;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<class AMiroWinProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* EmptyClipSound;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate = 0.f;

	float LastShootTimeStamp = -FireRate;
};