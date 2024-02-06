// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PPAIController.generated.h"

class UPPAIPerceptionComponent;
class UPPRespawnComponent;

UCLASS()
class PEWPEW_API APPAIController : public AAIController
{
	GENERATED_BODY()

public:
	APPAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPPAIPerceptionComponent* PPAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPPRespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
