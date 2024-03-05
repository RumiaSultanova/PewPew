// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PPBaseWidget.h"
#include "PPPauseWidget.generated.h"

class UButton;
UCLASS()
class PEWPEW_API UPPPauseWidget : public UPPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnClearPause();
};
