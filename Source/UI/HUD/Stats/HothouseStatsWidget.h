#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HothouseStatsWidget.generated.h"

UCLASS()
class UHothouseStatsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtInteraction;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtOccupied;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtHarvest;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtWater;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtBreakdown; 

private:
	UFUNCTION() void RefreshStats();

	FTimerHandle RefreshTimer;
};