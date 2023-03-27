// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiroWinHUD.generated.h"

UCLASS()
class AMiroWinHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMiroWinHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

