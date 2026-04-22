#pragma once

#include "CoreMinimal.h"
#include "HothouseStats.generated.h"

USTRUCT(BlueprintType)
struct FHothouseStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 OccupiedCells = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 ReadyToHarvestCount = 0;

	UPROPERTY(BlueprintReadOnly)
	float AverageWaterLevel = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, int32> PlantsCountByType;
};