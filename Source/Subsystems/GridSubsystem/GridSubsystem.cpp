#include "GridSubsystem.h"
#include "Core/GridSimulation.h"
#include "Settings/HothouseSettings.h"

void UGridSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    const UHothouseSettings* Settings = GetDefault<UHothouseSettings>();
    Grid.Init(Settings->GridWidth, Settings->GridHeight);
    CachedCropData = Settings->CropData.LoadSynchronous();
}

void UGridSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    const UHothouseSettings* Settings = GetDefault<UHothouseSettings>();
    InWorld.GetTimerManager().SetTimer(Timer, this, &UGridSubsystem::Tick, Settings->TickInterval, true);
}

void UGridSubsystem::Tick()
{
    if (CachedCropData)
    {
        FGridSimulation::Update(Grid, CachedCropData);
        Sync();
    }
}

void UGridSubsystem::Plant(int32 X, int32 Y, FName Type)
{
    if (Grid.IsValid(X, Y))
    {
        int32 Idx = Grid.GetIndex(X, Y);
        if (Grid.Cells[Idx].State == EHothouseCellState::Empty)
        {
            Grid.Cells[Idx].State = EHothouseCellState::Growing;
            Grid.Cells[Idx].CropType = Type;
            Grid.Cells[Idx].WaterLevel = 100.0f;
            Grid.Cells[Idx].GrowthProgress = 0.0f;
            Grid.MarkDirty(Idx);
            Sync();
        }
    }
}

bool UGridSubsystem::Harvest(int32 X, int32 Y, FName& OutType)
{
    if (Grid.IsValid(X, Y))
    {
        int32 Idx = Grid.GetIndex(X, Y);
        if (Grid.Cells[Idx].State == EHothouseCellState::ReadyToHarvest)
        {
            OutType = Grid.Cells[Idx].CropType;
            Grid.Cells[Idx] = FHothouseCell();
            Grid.MarkDirty(Idx);
            Sync();
            return true;
        }
    }
    return false;
}

void UGridSubsystem::WaterArea(int32 CenterX, int32 CenterY, int32 Radius)
{
    for (int32 y = CenterY - Radius; y <= CenterY + Radius; ++y)
    {
        for (int32 x = CenterX - Radius; x <= CenterX + Radius; ++x)
        {
            if (Grid.IsValid(x, y))
            {
                int32 Idx = Grid.GetIndex(x, y);
                Grid.Cells[Idx].WaterLevel = 100.0f;
                Grid.MarkDirty(Idx);
            }
        }
    }
    
    Sync();
}

FHothouseStats UGridSubsystem::GetStats() const
{
    FHothouseStats S;
    float TotalW = 0.0f;
    for (const auto& C : Grid.Cells)
    {
        TotalW += C.WaterLevel;
        if (C.State != EHothouseCellState::Empty)
        {
            S.OccupiedCells++;
            S.PlantsCountByType.FindOrAdd(C.CropType)++;
            if (C.State == EHothouseCellState::ReadyToHarvest) S.ReadyToHarvestCount++;
        }
    }
    S.AverageWaterLevel = Grid.Cells.Num() > 0 ? TotalW / Grid.Cells.Num() : 0.0f;
    return S;
}

void UGridSubsystem::Sync()
{
    TArray<int32> Dirty;
    for (TBitArray<>::FConstIterator It(Grid.DirtyMap); It; ++It)
    {
        if (It.GetValue()) Dirty.Add(It.GetIndex());
    }
    if (Dirty.Num() > 0)
    {
        OnUpdate.Broadcast(Dirty);
        Grid.DirtyMap.Init(false, Grid.Cells.Num());
    }
}

FHothouseSaveData UGridSubsystem::CreateSnapshot() const
{
    FHothouseSaveData D;
    D.Cells = Grid.Cells;
    D.Width = Grid.Width;
    D.Height = Grid.Height;
    return D;
}

void UGridSubsystem::LoadSnapshot(const FHothouseSaveData& Data)
{
    Grid.Width = Data.Width;
    Grid.Height = Data.Height;
    Grid.Cells = Data.Cells;
    Grid.DirtyMap.Init(true, Grid.Cells.Num());
    Sync();
}