// Pew-Pew Game. All Rights Reserved.

#include "AI/PPAIController.h"
#include "AI/PPAICharacter.h"
#include "Components/PPAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APPAIController::APPAIController()
{
	PPAIPerceptionComponent = CreateDefaultSubobject<UPPAIPerceptionComponent>("PPAIPerceptionComponent");
	SetPerceptionComponent(*PPAIPerceptionComponent);

	bWantsPlayerState = true;
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
	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* APPAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) { return nullptr; }
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}