// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PPBasePickup.generated.h"

class USphereComponent;

UCLASS()
class PEWPEW_API APPBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APPBasePickup();

protected:
	UPROPERTY(VisibleAnywhere, Category="Pickup")
	USphereComponent* CollisionComponent;

	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;

};
