// Pew-Pew Game. All Rights Reserved.

#include "Menu/PPMenuGameModeBase.h"
#include "Menu/PPMenuPlayerController.h"
#include "Menu/UI/PPMenuHUD.h"

APPMenuGameModeBase::APPMenuGameModeBase()
{
	PlayerControllerClass = APPMenuPlayerController::StaticClass();
	HUDClass = APPMenuHUD::StaticClass();
}
