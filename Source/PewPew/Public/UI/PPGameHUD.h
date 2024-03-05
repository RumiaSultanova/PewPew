// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PPCoreTypes.h"
#include "PPGameHUD.generated.h"

class UPPBaseWidget;

UCLASS()
class PEWPEW_API APPGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<EPPMatchState, UPPBaseWidget*> GameWidgets;

	UPROPERTY()
	UPPBaseWidget* CurrentWidget = nullptr;
	
	void DrawCrossHair();
	void OnMatchStateChanged(EPPMatchState State);
};
