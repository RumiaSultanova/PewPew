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

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<APPBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName WeaponAttachPointName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APPBaseWeapon* CurrentWeapon = nullptr;

	void SpawnWeapon();
};
