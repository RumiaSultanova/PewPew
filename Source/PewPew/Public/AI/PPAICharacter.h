// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/PPBaseCharacter.h"
#include "PPAICharacter.generated.h"

class UBehaviourTree;
class UWidgetComponent;

UCLASS()
class PEWPEW_API APPAICharacter : public APPBaseCharacter
{
	GENERATED_BODY()

public:
	APPAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree*BehaviourTreeAsset;

	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI")
	float HealthVisibilityDistance = 1000.0f;
	
	virtual void BeginPlay() override;
	 
	virtual void OnDeath() override;
	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void UpdateHealthWidgetVisibility();
};
