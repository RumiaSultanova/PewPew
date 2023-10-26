// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/PPBaseWeapon.h"
#include "PPRifleWeapon.generated.h"

UCLASS()
class PEWPEW_API APPRifleWeapon : public APPBaseWeapon
{
	GENERATED_BODY()

public:	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float BulletSpread = 1.5f;

	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
	FTimerHandle ShotTimerHandle;
};
