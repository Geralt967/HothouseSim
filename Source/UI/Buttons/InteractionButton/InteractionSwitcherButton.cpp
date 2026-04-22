#include "UI/Buttons/InteractionButton/InteractionSwitcherButton.h"
#include "Components/Button.h"
#include "PlayerController/HothousePlayerController.h"

void UInteractionSwitcherButton::NativeConstruct()
{
	Super::NativeConstruct();
	if (ModeButton) ModeButton->OnClicked.AddDynamic(this, &UInteractionSwitcherButton::OnClicked);
}

void UInteractionSwitcherButton::OnClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
		PC->ChangeInteractionMode();
}