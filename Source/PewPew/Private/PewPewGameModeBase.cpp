// Pew-Pew Game. All Rights Reserved.

#include "PewPewGameModeBase.h"

#include "AIController.h"
#include "Player/PPBaseCharacter.h"
#include "Player/PPPlayerController.h"
#include "UI/PPGameHUD.h"
#include "AIController.h"
#include "Player/PPPlayerState.h"
#include "PPUtils.h"
#include "Components/PPRespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGameModeBase, All, All);

constexpr  static int32 MinRoundTimeForRespawn = 10;

 APewPewGameModeBase::APewPewGameModeBase()
{
	DefaultPawnClass = APPBaseCharacter::StaticClass();
 	PlayerControllerClass = APPPlayerController::StaticClass();
 	HUDClass = APPGameHUD::StaticClass();
 	PlayerStateClass = APPPlayerState::StaticClass();
}

void APewPewGameModeBase::StartPlay()
{
	Super::StartPlay();

 	SpawnBots();
	CreateTeamsInfo();

 	CurrentRound = 1;
 	StartRound();
 	
 	SetMatchState(EPPMatchState::InProgress);
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
 			ResetPlayers();
 			StartRound();
 		}
	    else
	    {
	    	GameOver();
	    }
 	}
}

void APewPewGameModeBase::ResetPlayers()
{
 	if (!GetWorld()) { return; }

 	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
 	{
 		ResetOnePlayer(It->Get());
 	}
}

void APewPewGameModeBase::ResetOnePlayer(AController* Controller)
{
 	if (Controller  && Controller->GetPawn())
 	{
 		Controller->GetPawn()->Reset();
 	}
 	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void APewPewGameModeBase::CreateTeamsInfo()
{
 	if (!GetWorld()) { return; }

 	int32 TeamID = 0;
 	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
 	{
 		const auto Controller = It->Get();
 		if (!Controller) { continue; }

 		const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
 		if (!PlayerState) { continue; }

		PlayerState->SetTeamID(TeamID);
 		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
 		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		SetPlayerColor(Controller);

 		auto TeamsCount = GameData.TeamColors.Num();
 		if (TeamsCount == 0) { TeamsCount = 2; }
 		TeamID = (TeamID + 1) % TeamsCount;
 	}
}

FLinearColor APewPewGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
 	if (TeamID < GameData.TeamColors.Num())
 	{
 		return GameData.TeamColors[TeamID];
 	}

 	UE_LOG(LogPPGameModeBase, Warning, TEXT("No colour for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
 	return GameData.DefaultTeamColor;
}

void APewPewGameModeBase::SetPlayerColor(AController* Controller)
{
 	if (!Controller) { return; }

 	const auto Character = Cast<APPBaseCharacter>(Controller->GetPawn());
 	if (!Character) { return; }

 	const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
 	if (!PlayerState) { return; }

 	Character->SetPlayerColor(PlayerState->GetTeamColor());

}

void APewPewGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
	const auto KillerPlayerState = KillerController ? Cast<APPPlayerState>(KillerController->PlayerState) : nullptr; 	
	const auto VictimPlayerState = VictimController ? Cast<APPPlayerState>(VictimController->PlayerState) : nullptr; 	

	if (KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}

 	if (VictimPlayerState)
 	{
 		VictimPlayerState->AddDeath();
 	}

 	StartRespawn(VictimController);
}

void APewPewGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) { return; }
 	
 	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
 	{
 		const auto Controller = It->Get();
 		if (!Controller) { continue; }

 		const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
 		if (!PlayerState) { continue; }

 		PlayerState->LogInfo();
 	}
}

void APewPewGameModeBase::StartRespawn(AController* Controller)
{
 	const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
 	if (!RespawnAvailable) { return; }
 	
 	const auto RespawnComponent = PPUtils::GetPPPlayerComponent<UPPRespawnComponent>(Controller);
 	if (!RespawnComponent) { return; }

 	RespawnComponent->Respawn(GameData.RespawnTime);
}

void APewPewGameModeBase::RespawnRequest(AController* Controller)
{
	ResetOnePlayer(Controller);
}

bool APewPewGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

 	if (PauseSet)
 	{
 		SetMatchState(EPPMatchState::Pause);
 	}
 	
	return PauseSet;
}

bool APewPewGameModeBase::ClearPause()
{
 	const auto PauseCleared = Super::ClearPause();

 	if (PauseCleared)
 	{
 		SetMatchState(EPPMatchState::InProgress);
 	}
 	
 	return PauseCleared;
}

void APewPewGameModeBase::GameOver()
{
 	UE_LOG(LogPPGameModeBase, Display, TEXT("GAME OVER"))
 	LogPlayerInfo();

 	for (auto Pawn: TActorRange<APawn>(GetWorld()))
 	{
 		if (Pawn)
 		{
 			Pawn->TurnOff();
 			Pawn->DisableInput(nullptr);
 		}
 	}

 	SetMatchState(EPPMatchState::GameOver);
}

void APewPewGameModeBase::SetMatchState(EPPMatchState State)
{
 	if (MatchState == State){ return; }

 	MatchState = State;
 	OnMatchStateChanged.Broadcast(MatchState);
}
