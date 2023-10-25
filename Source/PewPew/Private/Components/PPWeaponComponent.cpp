// Pew-Pew Game. All Rights Reserved.


#include "Components/PPWeaponComponent.h"
#include "Weapon/PPBaseWeapon.h"
#include "GameFramework/Character.h"

UPPWeaponComponent::UPPWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPPWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void UPPWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) { return; }

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character){ return; }

	CurrentWeapon = GetWorld()->SpawnActor<APPBaseWeapon>(WeaponClass);
	if (!CurrentWeapon){ return; }

	FAttachmentTransformRules AttachmentRules (EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void UPPWeaponComponent::Fire()
{
	if (!CurrentWeapon) { return; }
	CurrentWeapon->Fire();
}