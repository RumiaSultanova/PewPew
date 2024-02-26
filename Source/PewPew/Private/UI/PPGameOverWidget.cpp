// Pew-Pew Game. All Rights Reserved.

#include "UI/PPGameOverWidget.h"
#include "PewPewGameModeBase.h"
#include "PPUtils.h"
#include "Components/VerticalBox.h"
#include "Player/PPPlayerState.h"
#include "UI/PPPlayerStatRowWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPPGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (GetWorld())
	{
		const auto GameMode = Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &UPPGameOverWidget::OnMatchStateChanged);
		}
	}
	
	if (ResetLevelButton)
	{
	    ResetLevelButton->OnClicked.AddDynamic(this, &UPPGameOverWidget::OnResetLevel);
	}
}

void UPPGameOverWidget::OnMatchStateChanged(EPPMatchState State)
{
	if (State == EPPMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}

void UPPGameOverWidget::UpdatePlayerStat()
{
	if (!GetWorld() || !PlayerStatBox) { return; }

	PlayerStatBox->ClearChildren();
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) { return; }

		const auto PlayerState = Cast<APPPlayerState>(Controller->PlayerState);
		if (!PlayerState) { return; }

		const auto PlayerStatRowWidget = CreateWidget<UPPPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if (!PlayerStatRowWidgetClass) { return; }

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(PPUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(PPUtils::TextFromInt(PlayerState->GetDeathNum()));
		PlayerStatRowWidget->SetTeam(PPUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void UPPGameOverWidget::OnResetLevel()
{
    const FName CurrentLevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, CurrentLevelName);
}
