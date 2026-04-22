#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CropContextMenu.generated.h"

UCLASS()
class UCropContextMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitMenu();

protected:
	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ButtonContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCropSelectorButton> ButtonClass;
};