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

	virtual void BeginPlay() override;
};
