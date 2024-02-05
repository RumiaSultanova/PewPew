// Pew-Pew Game. All Rights Reserved.


#include "Components/PPAIPerceptionComponent.h"
#include "AIController.h"
#include "PPUtils.h"
#include "PPHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UPPAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) { return nullptr; }

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) { return nullptr; }

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) { return nullptr; }

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PerceiveActor: PerceiveActors)
	{
		const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(PerceiveActor);
		//const auto HealthComp = PerceiveActor->FindComponentByClass<UPPHealthComponent>();

		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const auto AreEnemies = PerceivePawn && PPUtils::AreEnemies(Controller, PerceivePawn->Controller);

		if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();

			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}
		}
	}
	return BestPawn;
}