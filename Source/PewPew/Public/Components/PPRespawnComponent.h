// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPRespawnComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PEWPEW_API UPPRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPRespawnComponent();

	void Respawn(int32 RespawnTime);

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown;

	void RespawnTimerUpdate();
};
