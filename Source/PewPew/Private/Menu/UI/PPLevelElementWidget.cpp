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
	if(LevelImage)
	{
		LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
	}
}

void UPPLevelElementWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &UPPLevelElementWidget::OnLevelElementClicked);
		LevelSelectButton->OnHovered.AddDynamic(this, &UPPLevelElementWidget::OnLevelElementHovered);
		LevelSelectButton->OnUnhovered.AddDynamic(this, &UPPLevelElementWidget::OnLevelElementUnhovered);
	}
}

void UPPLevelElementWidget::OnLevelElementClicked()
{
	OnLevelSelected.Broadcast(LevelData);
}

void UPPLevelElementWidget::OnLevelElementHovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPPLevelElementWidget::OnLevelElementUnhovered()
{
	if (FrameImage)
	{
		FrameImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
