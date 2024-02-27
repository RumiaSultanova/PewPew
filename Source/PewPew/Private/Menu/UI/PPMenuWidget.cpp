// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PPGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPMenuWidget, All, All)

void UPPMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UPPMenuWidget::OnStartGame);
	}
}

void UPPMenuWidget::OnStartGame()
{
	if (!GetWorld()) { return; }

	const auto PPGameInstance = GetWorld()->GetGameInstance<UPPGameInstance>();
	if (!PPGameInstance){ return; }

	if (PPGameInstance->GetStartupLevelName().IsNone())
	{
		UE_LOG(LogPPMenuWidget, Error, TEXT("Level name is NONE"));
		return;
	}
	
	UGameplayStatics::OpenLevel(this, PPGameInstance->GetStartupLevelName());
}
