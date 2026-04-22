#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "CellView.generated.h"

UCLASS()
class UCellView : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget)) UImage* CellImage;
	UPROPERTY(meta = (BindWidget)) UTextBlock* CropTypeText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* StatusText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* WaterLevelText;
	UPROPERTY(meta = (BindWidget)) UTextBlock* LightLevelText;
	
public:
	int32 CellX = 0;
	int32 CellY = 0;
	uint8 CurrentState = 0;

	void UpdateVisuals(float Progress, uint8 State, FName CropType, float LightLevel, float WaterLevel);
};