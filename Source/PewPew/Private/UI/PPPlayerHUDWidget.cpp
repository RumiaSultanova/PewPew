// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPlayerHUDWidget.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"

float UPPPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) { return 0.0f; }

	const auto Component = Player->GetComponentByClass(UPPHealthComponent::StaticClass());
	const auto HealthComponent = Cast<UPPHealthComponent>(Component);
	if (!HealthComponent) { return 0.0f; }

	return HealthComponent->GetHealthPercent();
}

bool UPPPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) { return false; }

	const auto Component = Player->GetComponentByClass(UPPWeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<UPPWeaponComponent>(Component);
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetWeaponUIData(UIData);
}