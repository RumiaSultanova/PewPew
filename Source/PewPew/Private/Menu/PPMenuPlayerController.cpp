// Pew-Pew Game. All Rights Reserved.

#include "Menu/PPMenuPlayerController.h"

void APPMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
