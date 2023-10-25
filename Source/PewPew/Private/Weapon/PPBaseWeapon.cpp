// Pew-Pew Game. All Rights Reserved.


#include "Weapon/PPBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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

