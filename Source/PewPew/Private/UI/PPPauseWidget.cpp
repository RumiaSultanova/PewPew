// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UPPPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UPPPauseWidget::OnClearPause);
	}
}

void UPPPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) { return; }

	GetWorld()->GetAuthGameMode()->ClearPause();
}
