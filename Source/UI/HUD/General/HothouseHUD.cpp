#include "HothouseHUD.h"

#include "UI/View/Cell/CellView.h"
#include "UI/Menu/Context//CropContextMenu.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "PlayerController/HothousePlayerController.h"
#include "Settings/HothouseSettings.h"
#include "Subsystems/GridSubsystem/GridSubsystem.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UHothouseHUD::NativeConstruct()
{
	Super::NativeConstruct();

	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	const auto* Sett = GetDefault<UHothouseSettings>();
	if (!GS || !Sett) return;

	GS->OnUpdate.AddDynamic(this, &UHothouseHUD::OnGridUpdated);

	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(Cast<AHothousePlayerController>(GetOwningPlayer()),
		                                  &AHothousePlayerController::ShowPauseMenu);
	}

	for (int32 y = 0; y < Sett->GridHeight; ++y)
	{
		for (int32 x = 0; x < Sett->GridWidth; ++x)
		{
			auto* Cell = CreateWidget<UCellView>(this, CellClass);
			if (Cell)
			{
				Cell->CellX = x;
				Cell->CellY = y;
				GridPanel->AddChildToUniformGrid(Cell, y, x);
				CellMap.Add(y * Sett->GridWidth + x, Cell);
			}
		}
	}

	if (ContextMenuClass)
	{
		ActiveMenu = CreateWidget<UCropContextMenu>(this, ContextMenuClass);
		if (ActiveMenu)
		{
			ActiveMenu->InitMenu();
			if (MenuContainer)
			{
				MenuContainer->AddChild(ActiveMenu);
				MenuContainer->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

void UHothouseHUD::NativeDestruct()
{
	if (auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>())
	{
		GS->OnUpdate.RemoveDynamic(this, &UHothouseHUD::OnGridUpdated);
	}
	Super::NativeDestruct();
}

FReply UHothouseHUD::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	HideContextMenu();
	return FReply::Unhandled();
}

void UHothouseHUD::OnGridUpdated(const TArray<int32>& Indices)
{
	auto* GS = GetWorld()->GetSubsystem<UGridSubsystem>();
	if (!GS) return;

	auto Snap = GS->CreateSnapshot();
	for (int32 Idx : Indices)
	{
		if (CellMap.Contains(Idx) && Snap.Cells.IsValidIndex(Idx))
		{
			CellMap[Idx]->UpdateVisuals(
			  Snap.Cells[Idx].GrowthProgress, 
			  (uint8)Snap.Cells[Idx].State, 
			  Snap.Cells[Idx].CropType,
			  Snap.Cells[Idx].LightLevel,
			  Snap.Cells[Idx].WaterLevel
		  );
		}
	}
}

void UHothouseHUD::HandleCellClick(UCellView* ClickedCell, const FVector2D& ScreenPosition)
{
	HideContextMenu();
	
	if (ClickedCell && ClickedCell->CurrentState == 0)
	{
		if (auto* PC = Cast<AHothousePlayerController>(GetOwningPlayer()))
		{
			PC->SetPendingPlantLocation(ClickedCell->CellX, ClickedCell->CellY);
		}

		if (MenuContainer)
		{
			UCanvasPanel* RootCanvas = Cast<UCanvasPanel>(GetRootWidget());


			if (RootCanvas)
			{
				FVector2D LocalPos = RootCanvas->GetTickSpaceGeometry().AbsoluteToLocal(ScreenPosition);

				if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MenuContainer))
				{
					CanvasSlot->SetPosition(LocalPos);
					MenuContainer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				}
			}
			else
			{
				if (UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(MenuContainer))
				{
					CanvasSlot->SetPosition(ScreenPosition);
					MenuContainer->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				}
			}
		}
	}
}

void UHothouseHUD::HideContextMenu()
{
	if (MenuContainer)
	{
		MenuContainer->SetVisibility(ESlateVisibility::Collapsed);
	}
}
