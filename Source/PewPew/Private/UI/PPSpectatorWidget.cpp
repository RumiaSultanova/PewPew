// Pew-Pew Game. All Rights Reserved.

#include "UI/PPSpectatorWidget.h"
#include "PPUtils.h"
#include "Components/PPRespawnComponent.h"


bool UPPSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = PPUtils::GetPPPlayerComponent<UPPRespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) { return false; }

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
