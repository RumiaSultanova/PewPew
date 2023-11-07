// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPlayerHUDWidget.h"
#include "Components/PPHealthComponent.h"

float UPPPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) { return 0.0f; }

	const auto Component = Player->GetComponentByClass(UPPHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UPPHealthComponent>(Component);
	if (!HealthComponent) { return 0.0f; }

	return HealthComponent->GetHealthPercent();
}