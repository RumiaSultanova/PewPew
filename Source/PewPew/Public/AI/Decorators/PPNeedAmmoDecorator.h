// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PPNeedAmmoDecorator.generated.h"

class APPBaseWeapon;

UCLASS()
class PEWPEW_API UPPNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPPNeedAmmoDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<APPBaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
