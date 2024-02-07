// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPSpectatorWidget.generated.h"

UCLASS()
class PEWPEW_API UPPSpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UFUNCTION (BlueprintCallable, Category = "UI")
	bool GetRespawnTime(int32& CountDownTime) const;
};
