// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PPHealthPercentBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PEWPEW_API UPPHealthPercentBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPPHealthPercentBTDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.6f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
