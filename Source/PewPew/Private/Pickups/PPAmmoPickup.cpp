// Pew-Pew Game. All Rights Reserved.

#include "Pickups/PPAmmoPickup.h"
#include "Components/PPHealthComponent.h"
#include "Components/PPWeaponComponent.h"
#include "PPUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool APPAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	const auto HealthComponent = PPUtils::GetPPPlayerComponent<UPPHealthComponent>(PlayerPawn);
	if (!HealthComponent || HealthComponent->IsDead()) { return false; }

	const auto WeaponComponent = PPUtils::GetPPPlayerComponent<UPPWeaponComponent>(PlayerPawn);
	if (!WeaponComponent) { return false; }

	return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}