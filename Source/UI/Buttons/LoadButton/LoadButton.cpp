#include "LoadButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "PlayerController/HothousePlayerController.h"

void ULoadButton::NativeConstruct()
{
	Super::NativeConstruct();
	if (ActionButton) ActionButton->OnClicked.AddDynamic(this, &ULoadButton::OnClicked);
	if (SlotNameText) SlotNameText->SetText(FText::FromString(SlotName));
}

void ULoadButton::OnClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		PC->LoadGame(SlotName);
	}
}