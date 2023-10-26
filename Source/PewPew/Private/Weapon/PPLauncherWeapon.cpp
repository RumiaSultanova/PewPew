// Pew-Pew Game. All Rights Reserved.


#include "Weapon/PPLauncherWeapon.h"
#include "Weapon/PPProjectile.h"
#include "Kismet/GameplayStatics.h"

void APPLauncherWeapon::StartFire()
{
	MakeShot();
}

void APPLauncherWeapon::MakeShot()
{
	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
	// set projectile params
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}