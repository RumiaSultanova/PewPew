// Pew-Pew Game. All Rights Reserved.


#include "PewPewGameModeBase.h"
#include "Player/PPBaseCharacter.h"
#include "Player/PPPlayerController.h"
#include "UI/PPGameHUD.h"

 APewPewGameModeBase::APewPewGameModeBase()
{
	DefaultPawnClass = APPBaseCharacter::StaticClass();
 	PlayerControllerClass = APPPlayerController::StaticClass();
 	HUDClass = APPGameHUD::StaticClass();
}