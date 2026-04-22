#include "CellView.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Models/InteractionModes.h"
#include "PlayerController/HothousePlayerController.h"
#include "Subsystems/GridSubsystem/GridSubsystem.h"
#include "UI/HUD/General/HothouseHUD.h"

void UCellView::NativeConstruct()
{
	Super::NativeConstruct();
	bIsFocusable = true;
}

FReply UCellView::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() != EKeys::LeftMouseButton) return FReply::Unhandled();

	auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer());
	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	if (!GS || !PC) return FReply::Unhandled();
	
	if (PC->InteractionMode == EInteractionMode::Water)
	{
		GS->WaterArea(CellX, CellY, 0);
		return FReply::Handled();
	}
	
	if (CurrentState == 2)
	{
		FName CurrentCropName("Empty");
		GS->Harvest(CellX, CellY, CurrentCropName);
		return FReply::Handled();
	}
	
	if (CurrentState == 0)
	{
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHothouseHUD::StaticClass());
		if (FoundWidgets.Num() > 0)
		{
			Cast<UHothouseHUD>(FoundWidgets[0])->HandleCellClick(this, InGeometry.GetAbsolutePosition());
		}
	}
	return FReply::Handled();
}

void UCellView::UpdateVisuals(float Progress, uint8 State, FName CropType, float LightLevel, float WaterLevel)
{
	CurrentState = State;
	
	if (StatusText)
	{
		StatusText->SetText((State == 0) ? FText::GetEmpty() : FText::AsPercent(Progress / 100.f));
	}
	
	if (CropTypeText)
	{
		if (State == 0)
		{
			CropTypeText->SetText(FText::FromString("Empty"));
			WaterLevelText->SetText(FText::GetEmpty());
			LightLevelText->SetText(FText::GetEmpty());
		}
		else
		{
			CropTypeText->SetText(FText::FromName(CropType));
			WaterLevelText->SetText(FText::Format(NSLOCTEXT("Namespace", "Key", "W: {0}"), FText::AsNumber(WaterLevel)));
			LightLevelText->SetText(FText::Format(NSLOCTEXT("Namespace", "Key", "L: {0}"), FText::AsNumber(LightLevel)));
		}
	}
	

}
