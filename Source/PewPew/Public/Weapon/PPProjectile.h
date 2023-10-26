// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPProjectile.generated.h"

class USphereComponent;

UCLASS()
class PEWPEW_API APPProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	APPProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	float CollisionRadius = 5.0f;

	virtual void BeginPlay() override;
};
