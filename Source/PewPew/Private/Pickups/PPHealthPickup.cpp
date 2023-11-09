// Pew-Pew Game. All Rights Reserved.

#include "Pickups/PPHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool APPHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
	return true;
}