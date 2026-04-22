#include "Core/GridSimulation.h"

void FGridSimulation::Update(FHothouseGrid& Grid, const UCropData* DB)
{
	if (!DB) return;
	for (int32 i = 0; i < Grid.Cells.Num(); ++i)
	{
		FHothouseCell& Cell = Grid.Cells[i];

		if (Cell.State != EHothouseCellState::Growing) continue;
		if (Cell.WaterLevel <= 0.0f) continue;

		float G = 1.0f;
		float W = 0.5f;
		
		if (const FCropModel* Def = DB->CropMap.Find(Cell.CropType))
		{
			G = Def->GrowthRate;
			W = Def->WaterConsumption;
		}

		Cell.GrowthProgress += G;
		Cell.WaterLevel = FMath::Max(0.0f, Cell.WaterLevel - W);

		if (Cell.GrowthProgress >= 100.0f)
		{
			Cell.GrowthProgress = 100.0f;
			Cell.State = EHothouseCellState::ReadyToHarvest;
		}

		Grid.MarkDirty(i);
	}
}