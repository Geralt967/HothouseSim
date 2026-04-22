#pragma once

#include "CoreMinimal.h"
#include "HothouseSaveData.h"
#include "ProgressModel.generated.h"

USTRUCT(BlueprintType)
struct FProgressModel
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString PlayerId;

	UPROPERTY(BlueprintReadWrite)
	FHothouseSaveData GreenhouseState;
};