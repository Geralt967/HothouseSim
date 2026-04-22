#include "SaveButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerController/HothousePlayerController.h"

void USaveButton::NativeConstruct()
{
	Super::NativeConstruct();
	if (ActionButton) ActionButton->OnClicked.AddDynamic(this, &USaveButton::OnClicked);
	if (SlotNameText) SlotNameText->SetText(FText::FromString(SlotName));
}

void USaveButton::OnClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		PC->SaveGame(SlotName);
	}
}