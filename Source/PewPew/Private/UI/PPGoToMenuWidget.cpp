// Pew-Pew Game. All Rights Reserved.

#include "UI/PPGoToMenuWidget.h"
#include "Components/Button.h"
#include "PPGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGoToMenuWidget, All, All)

void UPPGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UPPGoToMenuWidget::OnGoToMenu);
	}
}

void UPPGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld()) { return; }

	const auto PPGameInstance = GetWorld()->GetGameInstance<UPPGameInstance>();
	if (!PPGameInstance){ return; }

	if (PPGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogPPGoToMenuWidget, Error, TEXT("Menu name is NONE"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this, PPGameInstance->GetMenuLevelName());
}
