#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Buttons/LoadButton/LoadButton.h"
#include "MainMenuWidget.generated.h"


UCLASS()
class HOTHOUSESIMULATION_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnNewGame;

	UPROPERTY(meta = (BindWidget))
	class UPanelWidget* SaveListContainer;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULoadButton> LoadButtonClass;

	UFUNCTION() void OnNewGameClicked();

private:
	void PopulateSaveSlots();
};
