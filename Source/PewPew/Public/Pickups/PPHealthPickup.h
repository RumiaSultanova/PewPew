// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PPBasePickup.h"
#include "PPHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class PEWPEW_API APPHealthPickup : public APPBasePickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
