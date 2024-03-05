// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PPBaseWidget.h"
#include "PPCoreTypes.h"
#include "PPGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class PEWPEW_API UPPGameOverWidget : public UPPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
    UButton* ResetLevelButton;	

    virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(EPPMatchState State);
	void UpdatePlayerStat();
	
	UFUNCTION()
	void OnResetLevel();
};
