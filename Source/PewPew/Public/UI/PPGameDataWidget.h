// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPGameDataWidget.generated.h"

class APPPlayerState;
class APewPewGameModeBase;

UCLASS()
class PEWPEW_API UPPGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetDeathsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

private:
	APewPewGameModeBase* GetPPGameMode() const;
	APPPlayerState* GetPPPlayerState() const;
};
