#pragma once

#include "CoreMinimal.h"
#include "HothouseCell.h"

struct FHothouseGrid
{
	TArray<FHothouseCell> Cells;
	TBitArray<> DirtyMap;
	int32 Width = 0;
	int32 Height = 0;

	void Init(int32 InWidth, int32 InHeight)
	{
		Width = InWidth;
		Height = InHeight;
		Cells.Init(FHothouseCell(), Width * Height);
		DirtyMap.Init(false, Cells.Num());
	}

	bool IsValid(int32 X, int32 Y) const 
	{ 
		return X >= 0 && X < Width && Y >= 0 && Y < Height; 
	}

	int32 GetIndex(int32 X, int32 Y) const 
	{ 
		return Y * Width + X; 
	}

	void MarkDirty(int32 Index) 
	{ 
		if (DirtyMap.IsValidIndex(Index)) DirtyMap[Index] = true; 
	}
};
