// Pew-Pew Game. All Rights Reserved.

#include "AI/Services/PPFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PPUtils.h"
#include "Components/PPAIPerceptionComponent.h"

UPPFindEnemyService::UPPFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UPPFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = PPUtils::GetPPPlayerComponent<UPPAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}