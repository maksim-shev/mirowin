// Fill out your copyright notice in the Description page of Project Settings.


#include "MiroWin/Weapon/MiroWinAutoRifle.h"

#include "Kismet/GameplayStatics.h"
#include "MiroWin/MiroWinCharacter.h"
#include "MiroWin/MiroWinProjectile.h"

void UMiroWinAutoRifle::PullTrigger()
{
	Super::PullTrigger();

	if (GetAmmo() <= 0)
	{
		if (EmptyClipSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, EmptyClipSound, OwnerPawn->GetActorLocation());
		}

		return;
	}

	const UWorld* pWorld = GetWorld();
	if(!IsValid(pWorld))
	{
		return;
	}

	// to avoid "clicking" for quick fire, we add a delay if the trigger is pulled again before the cooldown has passed
	const float Delay = pWorld->GetTimeSeconds() - LastShootTimeStamp >= FireRate
		                    ? 0
		                    : FireRate - (pWorld->GetTimeSeconds() - LastShootTimeStamp);
	pWorld->GetTimerManager().SetTimer(ShootTimerHandle, this, &UMiroWinAutoRifle::Shoot, FireRate, true, Delay);
}

void UMiroWinAutoRifle::ReleaseTrigger()
{
	Super::ReleaseTrigger();

	const UWorld* pWorld = GetWorld();
	if (!IsValid(pWorld))
	{
		return;
	}

	pWorld->GetTimerManager().ClearTimer(ShootTimerHandle);
}

void UMiroWinAutoRifle::Shoot()
{
	if (GetAmmo() <= 0)
	{
		ReleaseTrigger();
	}

	// try and fire a projectile
	if (ProjectileClass && IsValid(OwnerPawn))
	{
		UWorld*  pWorld = GetWorld();
		if (IsValid(pWorld))
		{
			const FRotator SpawnRotation = OwnerPawn->GetControlRotation();
			const FVector SpawnLocation = OwnerPawn->GetShootLocation();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// spawn the projectile at the muzzle
			pWorld->SpawnActor<AMiroWinProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
		LastShootTimeStamp = pWorld->GetTimeSeconds();

		AddAmmo(-1);

		if (GetAmmo() <= 0)
		{
			// if the last bullet, then we use the same sound as for an empty clip
			if (IsValid(EmptyClipSound))
			{
				UGameplayStatics::PlaySoundAtLocation(this, EmptyClipSound, OwnerPawn->GetActorLocation(), 2.f);
			}
		}

		// try and play the sound if specified
		if (IsValid(FireSound))
		{
			// all these magic numbers will lower the pitch if there are less than 30 bullets left (30 bullets - 100% pitch, 0 bullets - 80% pitch)
			const float PitchMultiplier = FMath::Clamp(
				static_cast<float>(GetAmmo()) * 0.006f + 0.8f, 0.8f, 1.f);
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, OwnerPawn->GetActorLocation(), 1.f, PitchMultiplier);
		}
	}
}