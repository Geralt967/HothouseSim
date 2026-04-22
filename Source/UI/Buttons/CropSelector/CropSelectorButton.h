#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CropSelectorButton.generated.h"

UCLASS()
class UCropSelectorButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget)) class UButton* SelectButton;
	UPROPERTY(meta = (BindWidget)) class UTextBlock* CropNameText;
	UFUNCTION() void OnClicked();
public:
	FName CropId;
};