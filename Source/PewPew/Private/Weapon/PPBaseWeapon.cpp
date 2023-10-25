// Pew-Pew Game. All Rights Reserved.

#include "Weapon/PPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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
}

void APPBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire"));
}