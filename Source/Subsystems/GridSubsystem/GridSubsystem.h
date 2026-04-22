#pragma once

#include "Data/CropData.h"
#include "Subsystems/WorldSubsystem.h"
#include "Models/HothouseGrid.h"
#include "Models/HothouseSaveData.h"
#include "Models/HothouseStats.h"
#include "GridSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridUpdate, const TArray<int32>&, Indices);

UCLASS()
class UGridSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable)
	void Plant(int32 X, int32 Y, FName Type);

	UFUNCTION(BlueprintCallable)
	bool Harvest(int32 X, int32 Y, FName& OutType);

	UFUNCTION(BlueprintCallable)
	void WaterArea(int32 CenterX, int32 CenterY, int32 Radius);
	
	UFUNCTION(BlueprintPure)
	FHothouseStats GetStats() const;

	UFUNCTION(BlueprintPure)
	FHothouseSaveData CreateSnapshot() const;

	UFUNCTION(BlueprintCallable)
	void LoadSnapshot(const FHothouseSaveData& Data);

	UPROPERTY(BlueprintAssignable)
	FOnGridUpdate OnUpdate;

private:
	void Tick();
	void Sync();

	UPROPERTY()
	const UCropData* CachedCropData = nullptr;
	FHothouseGrid Grid;
	FTimerHandle Timer;
};