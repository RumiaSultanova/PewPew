// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPCoreTypes.h"
#include "PPLevelElementWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class PEWPEW_API UPPLevelElementWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const { return LevelData; }

	void SetSelected(bool IsSelected);

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* LevelSelectButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* LevelNameTextBlock;

	UPROPERTY(meta=(BindWidget))
	UImage* LevelImage;

	UPROPERTY(meta=(BindWidget))
	UImage* FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelElementClicked();
};
