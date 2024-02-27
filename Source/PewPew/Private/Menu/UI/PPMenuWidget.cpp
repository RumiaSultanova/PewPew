// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

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
	const FName StartupLevelName = "TestLevel";
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
