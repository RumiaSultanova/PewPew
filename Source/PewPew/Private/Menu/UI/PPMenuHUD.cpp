// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPMenuHUD.h"
#include "Blueprint/UserWidget.h"

void APPMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}
