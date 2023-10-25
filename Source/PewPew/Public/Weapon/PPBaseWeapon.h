// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class PEWPEW_API APPBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	APPBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;

	virtual void BeginPlay() override;

	void MakeShot();
};
