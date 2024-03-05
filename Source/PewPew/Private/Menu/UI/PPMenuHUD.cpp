// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPMenuHUD.h"
#include "UI/PPBaseWidget.h"

void APPMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UPPBaseWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}
