#include "CropContextMenu.h"
#include "UI/Menu/Context/CropContextMenu.h"
#include "Components/PanelWidget.h"
#include "UI/Buttons/CropSelector/CropSelectorButton.h"
#include "Settings/HothouseSettings.h"
#include "Data/CropData.h"

void UCropContextMenu::InitMenu()
{
	if (!ButtonContainer || !ButtonClass) return;

	ButtonContainer->ClearChildren();

	const auto* Sett = GetDefault<UHothouseSettings>();
	if (Sett && Sett->CropData.LoadSynchronous())
	{
		const UCropData* DB = Sett->CropData.Get();
		for (const auto& It : DB->CropMap)
		{
			auto* Btn = CreateWidget<UCropSelectorButton>(this, ButtonClass);
			if (Btn)
			{
				Btn->CropId = It.Key;
				ButtonContainer->AddChild(Btn);
			}
		}
	}
}
