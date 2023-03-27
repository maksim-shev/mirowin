// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/MiroWinWeapon.h"
#include "MiroWinCharacter.generated.h"

class UMiroWinWeapon;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAddedDelegate, UMiroWinWeapon*, _Weapon);

UCLASS(config=Game)
class AMiroWinCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMiroWinCharacter();

	UFUNCTION(BlueprintGetter, Category="Weapon")
	const TMap<EWeaponType, UMiroWinWeapon*>& GetAvailableWeapons() const { return AvailableWeapons; }

	UFUNCTION(BlueprintGetter, Category="Weapon")
	UMiroWinWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	UPROPERTY(BlueprintAssignable, Category="Weapon")
	FOnWeaponAddedDelegate OnWeaponAdded;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponAdded_BP();

	// the point from which shot will take place
	FVector GetShootLocation() const;

	void PlayFireAnimation() const;

protected:
	virtual void BeginPlay() override;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
	USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

protected:
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void OnFire();

	void StopFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	// Map of all weapons in the game. Stored in character for simplicity
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TMap<EWeaponType, TSubclassOf<UMiroWinWeapon>> AllWeapons;

	// All weapons available for using
	UPROPERTY(BlueprintGetter=GetAvailableWeapons, Category="Weapon")
	TMap<EWeaponType, UMiroWinWeapon*> AvailableWeapons;

	UPROPERTY(BlueprintGetter=GetCurrentWeapon, Category="Weapon")
	UMiroWinWeapon* CurrentWeapon;

	void AddWeapon(EWeaponType _WeaponType);
};