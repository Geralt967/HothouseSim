#include "UI/Buttons/CropSelector/CropSelectorButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerController/HothousePlayerController.h"

void UCropSelectorButton::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &UCropSelectorButton::OnClicked);
	}

	if (CropNameText)
	{
		CropNameText->SetText(FText::FromName(CropId));
	}
}

void UCropSelectorButton::OnClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		PC->TryPlantSelectedCrop(CropId);
	}
}