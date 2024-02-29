// Pew-Pew Game. All Rights Reserved.

#include "Menu/UI/PPLevelElementWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPPLevelElementWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;

	if (LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if (LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
}

void UPPLevelElementWidget::SetSelected(bool IsSelected)
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UPPLevelElementWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UPPLevelElementWidget::OnLevelElementClicked);
	}
}

void UPPLevelElementWidget::OnLevelElementClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}
