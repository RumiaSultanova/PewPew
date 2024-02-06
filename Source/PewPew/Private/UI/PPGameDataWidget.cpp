// Pew-Pew Game. All Rights Reserved.

#include "UI/PPGameDataWidget.h"
#include "PewPewGameModeBase.h"
#include "Player/PPPlayerState.h"

int32 UPPGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetPPPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 UPPGameDataWidget::GetDeathsNum() const
{
	const auto PlayerState = GetPPPlayerState();
	return PlayerState ? PlayerState->GetDeathNum() : 0;
}

int32 UPPGameDataWidget::GetCurrentRoundNum() const
{
	const auto GameMode = GetPPGameMode();
	return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 UPPGameDataWidget::GetTotalRoundNum() const
{
	const auto GameMode = GetPPGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UPPGameDataWidget::GetRoundSecondsRemaining() const
{
	const auto GameMode = GetPPGameMode();
	return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

APewPewGameModeBase* UPPGameDataWidget::GetPPGameMode() const
{
	return GetWorld() ? Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

APPPlayerState* UPPGameDataWidget::GetPPPlayerState() const
{
	return GetOwningPlayer() ? Cast<APPPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
