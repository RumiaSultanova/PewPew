// Pew-Pew Game. All Rights Reserved.

#include "PewPewGameModeBase.h"

#include "AIController.h"
#include "Player/PPBaseCharacter.h"
#include "Player/PPPlayerController.h"
#include "AIController.h"
#include "UI/PPGameHUD.h"

 APewPewGameModeBase::APewPewGameModeBase()
{
	DefaultPawnClass = APPBaseCharacter::StaticClass();
 	PlayerControllerClass = APPPlayerController::StaticClass();
 	HUDClass = APPGameHUD::StaticClass();
}

void APewPewGameModeBase::StartPlay()
{
	Super::StartPlay();

 	SpawnBots();
}

UClass* APewPewGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
 	if (InController && InController->IsA<AAIController>())
 	{
 		return AIPawnClass;
 	}
 	
 	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void APewPewGameModeBase::SpawnBots()
{
 	if (!GetWorld()){ return; }

 	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
 	{
 		FActorSpawnParameters SpawnInfo;
 		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

 		const auto PPAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
 		RestartPlayer(PPAIController);
 	}
}
