#include "UI/Menu/PauseMenu/PauseMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerController/HothousePlayerController.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (BtnResume) BtnResume->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
	if (BtnQuit) BtnQuit->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnQuitClicked);
	if (BtnSave) BtnSave->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnSaveClicked);
}

void UPauseMenuWidget::OnResumeClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		PC->StartGame();
	}
}

void UPauseMenuWidget::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UPauseMenuWidget::OnSaveClicked()
{
	if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
	{
		FString TimeStr = FDateTime::Now().ToString(TEXT("%Y-%m-%d_%H-%M-%S"));
		FString SlotName = FString::Printf(TEXT("Save_%s"), *TimeStr);

		PC->SaveGame(SlotName);
	}
}