// Pew-Pew Game. All Rights Reserved.


#include "AI/PPAIController.h"
#include "AI/PPAICharacter.h"

void APPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto PPCharacter = Cast<APPAICharacter>(InPawn);
	if (PPCharacter)
	{
		RunBehaviorTree(PPCharacter->BehaviourTreeAsset);
	}
}