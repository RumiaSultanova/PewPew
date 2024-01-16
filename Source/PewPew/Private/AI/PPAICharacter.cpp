// Pew-Pew Game. All Rights Reserved.


#include "AI/PPAICharacter.h"
#include "PPAIController.h"

APPAICharacter::APPAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = APPAIController::StaticClass();
}