#include "Subsystems/PersistenceSubsystem/PersistenceSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPersistenceSubsystem::SaveProfile(FString Slot, const FProgressModel& Profile)
{
	if (auto* S = Cast<UHothouseSaveObject>(UGameplayStatics::CreateSaveGameObject(UHothouseSaveObject::StaticClass())))
	{
		
		S->SaveTimestamp = FDateTime::Now();
		S->Data = Profile;
		UGameplayStatics::SaveGameToSlot(S, Slot, 0);
	}
}

bool UPersistenceSubsystem::LoadProfile(FString Slot, FProgressModel& OutProfile)
{
	if (auto* L = Cast<UHothouseSaveObject>(UGameplayStatics::LoadGameFromSlot(Slot, 0)))
	{
		OutProfile = L->Data;
		return true;
	}
	return false;
}

TArray<FString> UPersistenceSubsystem::GetSaveSlots()
{
	TArray<FString> Slots;
	IFileManager& FileManager = IFileManager::Get();
	FString SaveDir = FPaths::ProjectSavedDir() + TEXT("SaveGames/");
	FileManager.FindFiles(Slots, *SaveDir, TEXT(".sav"));
    
	for (FString& Slot : Slots)
	{
		Slot.RemoveFromEnd(TEXT(".sav"));
	}
	return Slots;
}
