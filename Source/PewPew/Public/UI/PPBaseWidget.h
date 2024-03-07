// Pew-Pew Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PPBaseWidget.generated.h"

UCLASS()
class PEWPEW_API UPPBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Show();
	
protected:
	UPROPERTY(meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* ShowAnimation; 
};