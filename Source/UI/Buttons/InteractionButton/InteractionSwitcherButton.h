#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Models/InteractionModes.h"
#include "InteractionSwitcherButton.generated.h"

UCLASS()
class UInteractionSwitcherButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget)) class UButton* ModeButton;
	UFUNCTION() void OnClicked();
public:
	UPROPERTY(EditAnywhere) EInteractionMode TargetMode;
};