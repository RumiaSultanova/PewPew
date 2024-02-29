// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PPGameInstance.h"
#include "Menu/UI/PPLevelElementWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPMenuWidget, All, All)

void UPPMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UPPMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UPPMenuWidget::OnQuitGame);
	}

	InitLevelElements();
}

void UPPMenuWidget::OnStartGame()
{
	const auto PPGameInstance = GetPPGameInstance();
	if (!PPGameInstance) { return; }
	
	UGameplayStatics::OpenLevel(this, PPGameInstance->GetStartupLevel().LevelName);
}

void UPPMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UPPMenuWidget::InitLevelElements()
{
	const auto PPGameInstance = GetPPGameInstance();
	if (!PPGameInstance) { return; }

	checkf(PPGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if (!LevelElementsBox){ return; }

	LevelElementsBox->ClearChildren();

	for (auto LevelData: PPGameInstance->GetLevelsData())
	{
		const auto LevelElementWidget = CreateWidget<UPPLevelElementWidget>(GetWorld(), LevelElementWidgetClass);
		if (!LevelElementWidget) { continue; }

		LevelElementWidget->SetLevelData(LevelData);
		//LevelElementWidget->OnLevelSelected.AddUObject(this, &UPPMenuWidget::OnLevelSelected); todo

		LevelElementsBox->AddChild(LevelElementWidget);
		LevelElementWidgets.Add(LevelElementWidget);
	}

	if (PPGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(PPGameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(PPGameInstance->GetStartupLevel());
	}
}

void UPPMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto PPGameInstance = GetPPGameInstance();
	if (!PPGameInstance) { return; }

	PPGameInstance->SetStartupLevel(Data);

	for (auto LevelElementWidget: LevelElementWidgets)
	{
		if (LevelElementWidget)
		{
			const auto IsSelected = Data.LevelName == LevelElementWidget->GetLevelData().LevelName;
			LevelElementWidget->SetSelected(IsSelected);
		}
	}
}

UPPGameInstance* UPPMenuWidget::GetPPGameInstance() const
{
	if (!GetWorld()) { return nullptr; }
	return GetWorld()->GetGameInstance<UPPGameInstance>();
}
