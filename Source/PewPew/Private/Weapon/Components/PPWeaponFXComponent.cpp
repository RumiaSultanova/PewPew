// Pew-Pew Game. All Rights Reserved.


#include "Weapon/Components/PPWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

UPPWeaponFXComponent::UPPWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPPWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
 }

