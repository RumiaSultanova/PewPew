// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/PPBaseCharacter.h"
#include "PPAICharacter.generated.h"

class UBehaviourTree;

UCLASS()
class PEWPEW_API APPAICharacter : public APPBaseCharacter
{
	GENERATED_BODY()

public:
	APPAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree*BehaviourTreeAsset;
	
protected:
	virtual void OnDeath() override;
};
