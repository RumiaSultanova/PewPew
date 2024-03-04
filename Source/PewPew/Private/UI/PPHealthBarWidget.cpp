// Pew-Pew Game. All Rights Reserved.

#include "UI/PPHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UPPHealthBarWidget::SetHealthPercent(float Percent)
{
	if (!HealthProgressBar){ return; }

	const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
	? ESlateVisibility::Hidden
	: ESlateVisibility::Visible;
	HealthProgressBar->SetVisibility(HealthBarVisibility);

	const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
	HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

	HealthProgressBar->SetPercent(Percent);
}
