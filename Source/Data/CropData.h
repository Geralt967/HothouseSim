// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Models/CropModel.h"
#include "CropData.generated.h"

UCLASS()
class HOTHOUSESIMULATION_API UCropData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, FCropModel> CropMap;
};
