// Pew-Pew Game. All Rights Reserved.

#include "UI/PPGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/PPBaseWidget.h"
#include "PewPewGameModeBase.h"

void APPGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void APPGameHUD::BeginPlay()
{ 
	Super::BeginPlay();

	GameWidgets.Add(EPPMatchState::InProgress, CreateWidget<UPPBaseWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EPPMatchState::Pause, CreateWidget<UPPBaseWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EPPMatchState::GameOver, CreateWidget<UPPBaseWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair: GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) { continue; }

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GetWorld())
	{
		const auto GameMode = Cast<APewPewGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &APPGameHUD::OnMatchStateChanged);
		}
	}
}

void APPGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void APPGameHUD::OnMatchStateChanged(EPPMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
		CurrentWidget->Show();
	}
}
