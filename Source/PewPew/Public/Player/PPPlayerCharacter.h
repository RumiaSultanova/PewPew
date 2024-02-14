// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/PPBaseCharacter.h"
#include "PPPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PEWPEW_API APPPlayerCharacter : public APPBaseCharacter
{
	GENERATED_BODY()
	
public:
	APPPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	virtual void OnDeath() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

private:
	bool WantsToRun = false;
	bool IsMovingForward = false;
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void OnStartRunning();
	void OnStopRunning();
};
