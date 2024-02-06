// Pew-Pew Game. All Rights Reserved.


#include "Player/PPPlayerController.h"
#include "Components/PPRespawnComponent.h"

APPPlayerController::APPPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<UPPRespawnComponent>("RespawnComponent");
}
