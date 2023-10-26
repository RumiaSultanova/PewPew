// Pew-Pew Game. All Rights Reserved.

#include "Weapon/PPLauncherWeapon.h"
#include "Weapon/PPProjectile.h"

void APPLauncherWeapon::StartFire()
{
	MakeShot();
}

void APPLauncherWeapon::MakeShot()
{
	if (!GetWorld()){ return; }

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) { return; }

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	APPProjectile* Projectile = GetWorld()->SpawnActorDeferred<APPProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->FinishSpawning(SpawnTransform);
	}
}