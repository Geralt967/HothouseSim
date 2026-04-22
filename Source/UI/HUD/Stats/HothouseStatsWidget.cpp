#include "HothouseStatsWidget.h"
#include "Components/TextBlock.h"
#include "Subsystems/GridSubsystem/GridSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Models/HothouseStats.h"
#include "PlayerController/HothousePlayerController.h"

void UHothouseStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetTimerManager().SetTimer(RefreshTimer, this, &UHothouseStatsWidget::RefreshStats, 0.5f, true);
}

void UHothouseStatsWidget::NativeDestruct()
{
	GetWorld()->GetTimerManager().ClearTimer(RefreshTimer);
	Super::NativeDestruct();
}

void UHothouseStatsWidget::RefreshStats()
{
	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer());
	if (!GS || !PC) return;
	
	FHothouseStats Stats = GS->GetStats();
	UEnum* EnumPtr = StaticEnum<EInteractionMode>();
	FText EnumText = EnumPtr->GetDisplayNameTextByValue((int64)PC->InteractionMode);
	
	if (TxtInteraction) TxtInteraction->SetText(EnumText);
	if (TxtOccupied) TxtOccupied->SetText(FText::FromString(FString::Printf(TEXT("%d"), Stats.OccupiedCells)));
	if (TxtHarvest)  TxtHarvest->SetText(FText::FromString(FString::Printf(TEXT("%d"), Stats.ReadyToHarvestCount)));
	if (TxtWater)    TxtWater->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), FMath::RoundToInt(Stats.AverageWaterLevel))));

	if (TxtBreakdown)
	{
		FString BreakdownStr = TEXT("Planted:\n");
		for (const auto& Pair : Stats.PlantsCountByType)
		{
			BreakdownStr += FString::Printf(TEXT(" - %s: %d\n"), *Pair.Key.ToString(), Pair.Value);
		}
		TxtBreakdown->SetText(FText::FromString(BreakdownStr));
	}
}