// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PPBasePickup.h"
#include "PPAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class PEWPEW_API APPAmmoPickup : public APPBasePickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
