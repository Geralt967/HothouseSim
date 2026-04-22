#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadButton.generated.h"


UCLASS()
class HOTHOUSESIMULATION_API ULoadButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget)) class UButton* ActionButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* SlotNameText;
	UFUNCTION() void OnClicked();
public:
	UPROPERTY(EditAnywhere) FString SlotName;
};
