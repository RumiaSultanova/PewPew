// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PPPlayerState.h"
#include "GameFramework/Character.h"
#include "PPBaseCharacter.generated.h"

class UPPHealthComponent;
class UPPWeaponComponent;
class USoundCue;

UCLASS()
class PEWPEW_API APPBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APPBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UPPHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UPPWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category="Material")
	FName MaterialColorName = "Paint Color";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Sound")
	USoundCue* DeathSound; 

	virtual void BeginPlay() override;
	virtual void OnDeath();

	virtual void OnHealthChanged(float Health, float HealthDelta);

public:	
	UFUNCTION(BlueprintCallable, Category="Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;

	virtual void Tick(float DeltaTime) override;
	virtual void TurnOff() override;
	virtual void Reset() override;
	
	void SetPlayerColor(const FLinearColor& Color);

private:
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
