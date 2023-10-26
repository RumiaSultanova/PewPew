// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class PEWPEW_API APPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	APPProjectile();

	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	float CollisionRadius = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
};
