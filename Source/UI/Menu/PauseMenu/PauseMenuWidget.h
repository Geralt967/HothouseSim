#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

UCLASS()
class HOTHOUSESIMULATION_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnResume;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnQuit;

	UPROPERTY(meta = (BindWidget))
	UButton* BtnSave;

	UFUNCTION() void OnResumeClicked();
	UFUNCTION() void OnQuitClicked();
	UFUNCTION() void OnSaveClicked();
};
