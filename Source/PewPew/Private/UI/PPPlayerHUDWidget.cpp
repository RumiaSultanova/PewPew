// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPlayerHUDWidget.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "PPUtils.h"

float UPPPlayerHUDWidget::GetHealthPercent() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	if (!HealthComponent) { return 0.0f; }

	return HealthComponent->GetHealthPercent();
}
 
bool UPPPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool UPPPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(GetOwningPlayerPawn());
	if (!WeaponComponent) { return false; }

	return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData) ;
}

bool UPPPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool UPPPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->StateName == NAME_Spectating;
}
