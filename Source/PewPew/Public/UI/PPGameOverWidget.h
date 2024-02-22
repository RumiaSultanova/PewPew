// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPCoreTypes.h"
#include "PPGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class PEWPEW_API UPPGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, Category="UI")
	UVerticalBox* PlayerStatBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
	void OnMatchStateChanged(EPPMatchState State);
	void UpdatePlayerStat();
};
