#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Models/InteractionModes.h"
#include "HothousePlayerController.generated.h"

UCLASS()
class AHothousePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	EInteractionMode InteractionMode = EInteractionMode::Plant;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	FName SelectedCropType = NAME_None;

	UFUNCTION()void ShowMainMenu();
	UFUNCTION() void StartGame();
	UFUNCTION() void ShowPauseMenu();
	UFUNCTION()void SaveGame(FString SlotName);
	UFUNCTION()void LoadGame(FString SlotName);

	void SetPendingPlantLocation(int32 X, int32 Y);
	void TryPlantSelectedCrop(FName CropId);
	void ChangeInteractionMode();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;

private:
	UPROPERTY() UUserWidget* ActiveWidget;
	void SetUI(TSubclassOf<UUserWidget> Class, bool bGameMode);
	int32 PendingX = -1;
	int32 PendingY = -1;
};
