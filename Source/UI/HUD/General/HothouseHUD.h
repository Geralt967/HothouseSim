#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/UniformGridPanel.h"
#include "HothouseHUD.generated.h"


UCLASS()
class UHothouseHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void HandleCellClick(class UCellView* ClickedCell, const FVector2D& ScreenPosition);
	void HideContextMenu();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget)) class UUniformGridPanel* GridPanel;
	UPROPERTY(meta = (BindWidget)) class UButton* PauseButton;
	UPROPERTY(meta = (BindWidget)) class USizeBox* MenuContainer;
	UPROPERTY(meta = (BindWidget)) class UHothouseStatsWidget* StatsPanel;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UCellView> CellClass;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<class UCropContextMenu> ContextMenuClass;

	UFUNCTION() void OnGridUpdated(const TArray<int32>& Indices);

private:
	UPROPERTY() TMap<int32, UCellView*> CellMap;
	UPROPERTY() class UCropContextMenu* ActiveMenu;
};