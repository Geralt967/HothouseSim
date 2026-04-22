#include "UI/Menu/MainMenu/MainMenuWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "PlayerController/HothousePlayerController.h"
#include "Subsystems/PersistenceSubsystem/PersistenceSubsystem.h"
#include "UI/Buttons/LoadButton/LoadButton.h"


void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
	if (BtnNewGame) 
		BtnNewGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);

	PopulateSaveSlots();
}

void UMainMenuWidget::OnNewGameClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		PC->StartGame();
	}
}

void UMainMenuWidget::PopulateSaveSlots()
{
	if (!SaveListContainer || !LoadButtonClass) return;

	SaveListContainer->ClearChildren();
	auto* GI = GetWorld()->GetGameInstance();
	auto* PS = GI->GetSubsystem<UPersistenceSubsystem>();
	for (const FString& S : PS->GetSaveSlots())
	{
		auto* Widget = CreateWidget<ULoadButton>(this, LoadButtonClass);
		Widget->SlotName = S;
		SaveListContainer->AddChild(Widget);
	}
}
