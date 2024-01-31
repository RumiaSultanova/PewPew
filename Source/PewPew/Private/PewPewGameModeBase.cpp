// Pew-Pew Game. All Rights Reserved.

#include "PewPewGameModeBase.h"

#include "AIController.h"
#include "Player/PPBaseCharacter.h"
#include "Player/PPPlayerController.h"
#include "AIController.h"
#include "UI/PPGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGameModeBase, All, All);

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

 	CurrentRound = 1;
 	StartRound();
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

void APewPewGameModeBase::StartRound()
{
 	RoundCountDown = GameData.RoundTime;
 	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &APewPewGameModeBase::GameTimerUpdate, 1.0f, true);
}

void APewPewGameModeBase::GameTimerUpdate()
{
 	UE_LOG(LogPPGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

	/*
	const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
 	RoundCountDown -= TimerRate;
 	*/

 	if (--RoundCountDown == 0)
 	{
 		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

 		if(CurrentRound + 1 <= GameData.RoundsNum)
 		{
 			++CurrentRound;
 			StartRound();
 		}
	    else
	    {
		    UE_LOG(LogPPGameModeBase, Display, TEXT("GAME OVER"))
	    }
 	}
}
