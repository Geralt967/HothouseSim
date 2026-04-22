#pragma once

#include "CoreMinimal.h"
#include "CropModel.generated.h"

USTRUCT(BlueprintType)
struct FCropModel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GrowthRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaterConsumption = 1.0f;
};