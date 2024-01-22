// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/PPWeaponComponent.h"
#include "PPAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class PEWPEW_API UPPAIWeaponComponent : public UPPWeaponComponent
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
