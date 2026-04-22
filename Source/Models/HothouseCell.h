#pragma once

#include "CoreMinimal.h"
#include "HothouseCell.generated.h"

UENUM(BlueprintType)
enum class EHothouseCellState : uint8
{
	Empty,
	Growing,
	ReadyToHarvest,
	Blocked
};

USTRUCT(BlueprintType)
struct FHothouseCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EHothouseCellState State = EHothouseCellState::Empty;

	UPROPERTY(BlueprintReadWrite)
	FName CropType = NAME_None;

	UPROPERTY(BlueprintReadWrite)
	float WaterLevel = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float LightLevel = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float GrowthProgress = 0.0f;
};