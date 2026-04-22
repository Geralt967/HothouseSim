#pragma once
#include "Data/CropData.h"
#include "Models/HothouseGrid.h"

class FGridSimulation
{
public:
	static void Update(FHothouseGrid& Grid, const UCropData* DB);
};
