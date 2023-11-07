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
 
bool UPPPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UPPPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = GetWeaponComponent();
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

UPPWeaponComponent* UPPPlayerHUDWidget::GetWeaponComponent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) { return nullptr; }

	const auto Component = Player->GetComponentByClass(UPPWeaponComponent::StaticClass());
	return  Cast<UPPWeaponComponent>(Component);
}