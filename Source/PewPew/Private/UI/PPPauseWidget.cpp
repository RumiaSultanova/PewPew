// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool UPPPauseWidget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UPPPauseWidget::OnClearPause);
	}

	return InitStatus;
}

void UPPPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) { return; }

	GetWorld()->GetAuthGameMode()->ClearPause();
}
