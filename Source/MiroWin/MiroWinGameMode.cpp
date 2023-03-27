// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiroWinGameMode.h"
#include "MiroWinHUD.h"

AMiroWinGameMode::AMiroWinGameMode()
	: Super()
{
	// use our custom HUD class
	HUDClass = AMiroWinHUD::StaticClass();
}