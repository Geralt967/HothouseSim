#pragma once

#include "CoreMinimal.h"
#include "HothouseCell.h"
#include "HothouseSaveData.generated.h"

USTRUCT(BlueprintType)
struct FHothouseSaveData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FHothouseCell> Cells;

	UPROPERTY(BlueprintReadWrite)
	int32 Width = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Height = 0;
};