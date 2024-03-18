// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PPBaseWeapon.h"
#include "PPLauncherWeapon.generated.h"

class APPProjectile;
class USoundCue;

UCLASS()
class PEWPEW_API APPLauncherWeapon : public APPBaseWeapon
{
	GENERATED_BODY()

public:	
	virtual void StartFire();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	TSubclassOf<APPProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	USoundCue* NoAmmoSound; 

	virtual void MakeShot();
};