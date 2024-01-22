// Pew-Pew Game. All Rights Reserved.


#include "AI/PPAICharacter.h"
#include "PPAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PPAIWeaponComponent.h"

APPAICharacter::APPAICharacter(const FObjectInitializer& ObjInit)
:Super(ObjInit.SetDefaultSubobjectClass<UPPAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = APPAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}