// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GridFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HOTHOUSESIMULATION_API UGridFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static void IndexToCoord(int32 Idx, int32 W, int32& X, int32& Y)
	{
		X = Idx % W;
		Y = Idx / W;
	}
};
