// Pew-Pew Game. All Rights Reserved.

#include "UI/PPPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPPPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if (!PlayerNameTextBlock) { return; }
	PlayerNameTextBlock->SetText(Text);
}

void UPPPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!KillsTextBlock) { return; }
	KillsTextBlock->SetText(Text);
}

void UPPPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!DeathsTextBlock) { return; }
	DeathsTextBlock->SetText(Text);
}

void UPPPlayerStatRowWidget::SetTeam(const FText& Text)
{
	if (!TeamTextBlock) { return; }
	TeamTextBlock->SetText(Text);
}

void UPPPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerIndicatorImage) { return; }
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
