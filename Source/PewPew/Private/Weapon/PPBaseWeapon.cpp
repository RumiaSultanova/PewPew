// Pew-Pew Game. All Rights Reserved.

#include "Weapon/PPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DisplayDebugHelpers.h"
#include "Viewports.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

APPBaseWeapon::APPBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void APPBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(WeaponMesh);
}

void APPBaseWeapon::Fire()
{
	MakeShot();
}

void APPBaseWeapon::MakeShot()
{
	if (!GetWorld()){ return; }

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) { return; }

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f); 
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

APlayerController* APPBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if(!Player) { return nullptr; }

	return  Player->GetController<APlayerController>();
}

bool APPBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetPlayerController();
	if (!Controller) { return false; }

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

FVector APPBaseWeapon::GetMuzzleWorldLocation() const
{
	WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool APPBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) { return false; }

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void APPBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if (!GetWorld()){ return; }

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}