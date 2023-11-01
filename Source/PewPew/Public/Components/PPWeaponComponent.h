// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PPWeaponComponent.generated.h"

class APPBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PEWPEW_API UPPWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPPWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TArray<TSubclassOf<APPBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY()
	APPBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<APPBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;
	bool EquipAnimInProgress = false;

	void SpawnWeapons();
	void AttachWeaponToSocket(APPBaseWeapon* Weapon, USceneComponent* Mesh, const FName& Name);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
};
