// Pew-Pew Game. All Rights Reserved.

#include "AI/Decorators/PPHealthPercentBTDecorator.h"
#include "AIController.h"
#include "PPUtils.h"
#include "Components/PPHealthComponent.h"

UPPHealthPercentBTDecorator::UPPHealthPercentBTDecorator()
{
	NodeName = "Health Percent";
}

bool UPPHealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) { return false; }

	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead()) { return false; }

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
