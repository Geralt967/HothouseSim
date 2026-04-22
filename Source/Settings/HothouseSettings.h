#pragma once

#include "CoreMinimal.h"
#include "Data/CropData.h"
#include "Engine/DeveloperSettings.h"
#include "HothouseSettings.generated.h"


UCLASS(Config=Game, defaultconfig)
class HOTHOUSESIMULATION_API UHothouseSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UCropData> CropData;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	int32 GridWidth = 20;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	int32 GridHeight = 20;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	int32 BrushRadius = 1;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly)
	float TickInterval = 1.0f;
};
