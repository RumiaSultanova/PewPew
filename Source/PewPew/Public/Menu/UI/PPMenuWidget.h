// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/PPBaseWidget.h"
#include "PPCoreTypes.h"
#include "PPMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UPPGameInstance;
class UPPLevelElementWidget;

UCLASS()
class PEWPEW_API UPPMenuWidget : public UPPBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta=(BindWidget))
	UButton* QuitGameButton;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* LevelElementsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> LevelElementWidgetClass;	
	
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TArray<UPPLevelElementWidget*> LevelElementWidgets;
	
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelElements();
	void OnLevelSelected(const FLevelData& Data);
	UPPGameInstance* GetPPGameInstance() const;
};
