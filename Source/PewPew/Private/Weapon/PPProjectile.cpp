// Pew-Pew Game. All Rights Reserved.


#include "Weapon/PPProjectile.h"
#include "Components/SphereComponent.h"

APPProjectile::APPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(CollisionRadius);
	SetRootComponent(CollisionComponent);
}

void APPProjectile::BeginPlay()
{
	Super::BeginPlay();
}