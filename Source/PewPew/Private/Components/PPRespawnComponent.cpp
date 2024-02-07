// Pew-Pew Game. All Rights Reserved.

#include "Components/PPRespawnComponent.h"
#include "PewPewGameModeBase.h"

UPPRespawnComponent::UPPRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPPRespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) { return; }

	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UPPRespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UPPRespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UPPRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld()) { return; }
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) { return; }

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}
