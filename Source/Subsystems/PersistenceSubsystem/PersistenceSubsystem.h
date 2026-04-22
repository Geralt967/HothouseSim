#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Models/ProgressModel.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PersistenceSubsystem.generated.h"

UCLASS()
class UHothouseSaveObject : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FDateTime SaveTimestamp;
	
	UPROPERTY()
	FProgressModel Data;
};

UCLASS()
class HOTHOUSESIMULATION_API UPersistenceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SaveProfile(FString Slot, const FProgressModel& Profile);

	UFUNCTION(BlueprintCallable)
	bool LoadProfile(FString Slot, FProgressModel& OutProfile);

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetSaveSlots();
};
