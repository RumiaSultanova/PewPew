// Pew-Pew Game. All Rights Reserved.

#include "AI/Services/PPFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PPUtils.h"
#include "Components/PPWeaponComponent.h"

UPPFireService::UPPFireService()
{
	NodeName = "Fire";
}

void UPPFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller)
	{
		const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent)
		{
			HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}