#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveButton.generated.h"

UCLASS()
class USaveButton : public UUserWidget
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