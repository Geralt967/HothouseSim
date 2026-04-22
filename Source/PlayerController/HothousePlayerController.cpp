#include "HothousePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Subsystems/PersistenceSubsystem/PersistenceSubsystem.h"
#include "Subsystems/GridSubsystem/GridSubsystem.h"
#include "UI/HUD/General/HothouseHUD.h"

void AHothousePlayerController::BeginPlay() 
{ 
	Super::BeginPlay(); 
	bShowMouseCursor = true; 
	ShowMainMenu(); 
}

void AHothousePlayerController::SetUI(TSubclassOf<UUserWidget> Class, bool bGameMode)
{
	if (ActiveWidget) ActiveWidget->RemoveFromParent();
	if (!Class) return;
	ActiveWidget = CreateWidget<UUserWidget>(this, Class);
	ActiveWidget->AddToViewport();
	if (bGameMode) SetInputMode(FInputModeGameAndUI());
	else SetInputMode(FInputModeUIOnly());
}

void AHothousePlayerController::ShowMainMenu()
{
	SetUI(MainMenuClass, false);
}

void AHothousePlayerController::StartGame()
{
	SetUI(HUDClass, true);
}

void AHothousePlayerController::ShowPauseMenu()
{
	SetUI(PauseMenuClass, false);
}

void AHothousePlayerController::SaveGame(FString SlotName)
{
	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	auto* PS = GetGameInstance()->GetSubsystem<UPersistenceSubsystem>();
	if (GS && PS && !SlotName.IsEmpty()) 
	{ 
		FProgressModel M; 
		M.GreenhouseState = GS->CreateSnapshot(); 
		PS->SaveProfile(SlotName, M); 
	}
}

void AHothousePlayerController::LoadGame(FString SlotName)
{
	auto* PS = GetGameInstance()->GetSubsystem<UPersistenceSubsystem>();
	FProgressModel M;
	if (PS && !SlotName.IsEmpty() && PS->LoadProfile(SlotName, M))
	{
		if (auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>()) 
			GS->LoadSnapshot(M.GreenhouseState);
		StartGame();
	}
}

void AHothousePlayerController::SetPendingPlantLocation(int32 X, int32 Y)
{
	PendingX = X; PendingY = Y;
}

void AHothousePlayerController::TryPlantSelectedCrop(FName CropId)
{
	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	if (GS && PendingX != -1 && PendingY != -1)
	{
		GS->Plant(PendingX, PendingY, CropId);
		PendingX = -1; PendingY = -1;

		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHothouseHUD::StaticClass());
    
		if (FoundWidgets.Num() > 0)
		{
			if (auto* HUD = Cast<UHothouseHUD>(FoundWidgets[0]))
			{
				HUD->HideContextMenu();
			}
		}
	}
}

void AHothousePlayerController::ChangeInteractionMode()
{
	if (InteractionMode == EInteractionMode::Plant)
	{
		InteractionMode = EInteractionMode::Water;
	}
	else if (InteractionMode == EInteractionMode::Water)
	{
		InteractionMode = EInteractionMode::Plant;
	}
}
