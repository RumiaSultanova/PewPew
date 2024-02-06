// Pew-Pew Game. All Rights Reserved.

#include "AI/PPAIController.h"

#include "PPRespawnComponent.h"
#include "AI/PPAICharacter.h"
#include "Components/PPAIPerceptionComponent.h"
#include "Components/PPRespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

APPAIController::APPAIController()
{
	PPAIPerceptionComponent = CreateDefaultSubobject<UPPAIPerceptionComponent>("PPAIPerceptionComponent");
	SetPerceptionComponent(*PPAIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<UPPRespawnComponent>("RespawnComponent");
	
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