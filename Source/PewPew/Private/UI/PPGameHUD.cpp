// Pew-Pew Game. All Rights Reserved.

#include "UI/PPGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "PewPewGameModeBase.h"

void APPGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void APPGameHUD::BeginPlay()
{ 
	Super::BeginPlay();

	GameWidgets.Add(EPPMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(EPPMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));

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
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
