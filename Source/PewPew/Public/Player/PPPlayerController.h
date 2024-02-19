// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPCoreTypes.h"
#include "PPPlayerController.generated.h"

class UPPRespawnComponent;

UCLASS()
class PEWPEW_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APPPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPPRespawnComponent* RespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override; 

private:
	void OnPauseGame();
	void OnMatchStateChanged(EPPMatchState State);
};
