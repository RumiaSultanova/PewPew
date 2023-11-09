// Pew-Pew Game. All Rights Reserved.

#include "Pickups/PPAmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool APPAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
	return true;
}