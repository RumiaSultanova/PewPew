// Pew-Pew Game. All Rights Reserved.

#include "Player/PPPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPPlayerState, All, All);

void APPPlayerState::LogInfo()
{
	UE_LOG(LogPPPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathNum);
}
