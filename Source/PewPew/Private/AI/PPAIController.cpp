// Pew-Pew Game. All Rights Reserved.

#include "AI/PPAIController.h"
#include "AI/PPAICharacter.h"
#include "Components/PPAIPerceptionComponent.h"

APPAIController::APPAIController()
{
	PPAIPerceptionComponent = CreateDefaultSubobject<UPPAIPerceptionComponent>("PPAIPerceptionComponent");
	SetPerceptionComponent(*PPAIPerceptionComponent);
}

void APPAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto PPCharacter = Cast<APPAICharacter>(InPawn);
	if (PPCharacter)
	{
		RunBehaviorTree(PPCharacter->BehaviourTreeAsset);
	}
}

void APPAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto AimActor = PPAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}