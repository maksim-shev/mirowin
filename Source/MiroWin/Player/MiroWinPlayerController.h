// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiroWinPlayerController.generated.h"

/**
 *
 */
UCLASS()
class MIROWIN_API AMiroWinPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Player Controller")
	virtual void FlushPressedKeys() override;
};