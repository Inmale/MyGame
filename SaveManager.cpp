// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveManager.h"
#include "SaveGameMetadata.h"
#include "SaveGameData.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

FString USaveManager::CurrentSaveSlot;
TArray<TScriptInterface<ISaveInterface>> USaveManager::SaveInterfaces;

static const FString KMetadataSaveSlot = "SaveGameMetadata";
static const int32 kMaxSaveSlot = 20;

void USaveManager::Init()
{
	CurrentSaveSlot = "Default";

	//Make sure the metadata file exists incase the game has never ran
	USaveGame* saveGameMetadata = UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0);

	if (saveGameMetadata == nullptr)
	{
		//Since the metadata file doens't exist, we need to create one
		USaveGame* saveGameObject = UGameplayStatics::CreateSaveGameObject(USaveGameMetadata::StaticClass());

		UGameplayStatics::SaveGameToSlot(saveGameObject, KMetadataSaveSlot, 0);
	}
}

void USaveManager::QueryAllSaveInterfaces()
{
	//Clear old entries
	SaveInterfaces.Empty();

	//Get all the actors that implement the save interface
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, USaveInterface::StaticClass(), actors);

	for (auto actor : actors)
	{
		SaveInterfaces.Add(actor);
	}
}

void USaveManager::SaveGame()
{
	QueryAllSaveInterfaces();
	//Create a new save game data instance
	USaveGameData* saveGameData = Cast<USaveGameData>(UGameplayStatics::CreateSaveGameObject(USaveGameData::StaticClass()));

	//Get player character
	AMainCharacter* character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));

	if (character != nullptr)
	{
		//Save inventory item array to the save game object
		saveGameData->SetSaveItems(character->GetItems());

		//Save world objects to the save game object
		saveGameData->SetItemsMetadata(character->GetList());

		//Save all quests
		saveGameData->SetQuest(character->GetAllQuests());

		//Save world of time
		saveGameData->SetWorldTime(character->GetWorldTime());

		//Save all notes and peoples
		saveGameData->SetNotes(character->GetAllNotes());

		//Save list of containers
		saveGameData->SetContMetadata(character->GetListContainer());

		//Save overlapped actors
		saveGameData->SetSavedOverActors(character->GetSavedOverActors());

		//Save can be see tutorial
		saveGameData->SetIsSawTutorial(character->GetIsSawTutorial());

		//Save active dialogs
		saveGameData->SetActiveDialogs(character->GetActiveDialogs());

		TArray<FString> Names;

		character->SerializedData.GetKeys(Names);

		for (auto& i : Names)
		{
			FSaveData* sData = character->SerializedData.Find(i);
			if (sData != nullptr)
			{
				FSaveData& aData = saveGameData->SerializedData.Add(i);
				aData = *sData;
			}
		}
	}

	//Go over all the actors that need to be saved and save them
	for (auto& saveInterface : SaveInterfaces)
	{
		if (saveInterface.GetObject() == nullptr)
			continue;

		//Let the object know that it's about to ve saved
		saveInterface->Execute_OnBeforeSave(saveInterface.GetObject());

		//Find the object's save data using it's unique name
		FString uniqueSaveName = saveInterface->Execute_GetUniqueSaveName(saveInterface.GetObject());
		FSaveData& saveData = saveGameData->SerializedData.Add(uniqueSaveName);

		FMemoryWriter memoryWriter = FMemoryWriter(saveData.Data);
		memoryWriter.ArIsSaveGame = true;

		saveInterface.GetObject()->Serialize(memoryWriter);
	}

	//Save the game to the current slot
	UGameplayStatics::SaveGameToSlot(saveGameData, CurrentSaveSlot, 0);

	//Update the metadata file with the new slot
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0));

	FSaveMetadata& saveMetadata = saveGameMetadata->SavedGamesMetadata.FindOrAdd(CurrentSaveSlot);
	saveMetadata.SlotName = CurrentSaveSlot;
	saveMetadata.Date = FDateTime::Now();
	if (character != nullptr)
		saveMetadata.MapName = character->GetCurrentMapName();

	//Save the changes to the metadata file
	UGameplayStatics::SaveGameToSlot(saveGameMetadata, KMetadataSaveSlot, 0);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Cyan, "Saved: " + CurrentSaveSlot);
}

void USaveManager::LoadGame()
{
	QueryAllSaveInterfaces();
	USaveGameData* saveGameData = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));

	if (saveGameData == nullptr)
	{
		//No saves exists yet for this slot. Save a default one
		SaveGame();

		//Reload it
		saveGameData = Cast<USaveGameData>(UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));
	}

	//loop over all the actors that need to load data and load their data
	for (auto& saveInterface : SaveInterfaces)
	{
		if (saveInterface.GetObject() == nullptr)
			continue;

		//Find the object's save data using it's unique name
		FString uniqueSaveName = saveInterface->Execute_GetUniqueSaveName(saveInterface.GetObject());
		FSaveData* saveData = saveGameData->SerializedData.Find(uniqueSaveName);
		if (saveData == nullptr)
			continue;

		//Deserialize the object's save data
		FMemoryReader memoryReader = FMemoryReader(saveData->Data);
		memoryReader.ArIsSaveGame = false;

		saveInterface.GetObject()->Serialize(memoryReader);
	}

	//Get player character
	AMainCharacter* character = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld, 0));

	if (character != nullptr)
	{
		//Set inventory item array to the save game object
		character->SetItems(saveGameData->GetSaveItems());

		//Set world objects to the save game object
		character->SetList(saveGameData->GetItemsMetadata());

		//Set saved quests
		character->SetQuest(saveGameData->GetQuests());

		//Set world of time
		character->SetWorldTime(saveGameData->GetWorldTime());

		//Set all notes in jornal
		character->SetJornal(saveGameData->GetAllNotes());

		//Set all containers in game
		character->SetListContainer(saveGameData->GetContMetadata());

		//Set overlapping actors
		character->SetSavedOverActors(saveGameData->GetSavedOverActors());

		//Set can be see tutorial
		character->SetIsSawTutorial(saveGameData->GetIsSawTutorial());

		//Set active dialogs
		character->SetActiveDialogs(saveGameData->GetActiveDialogs());

		TArray<FString> Names;

		saveGameData->SerializedData.GetKeys(Names);

		for (auto& i : Names)
		{
			FSaveData* sData = saveGameData->SerializedData.Find(i);
			if (sData != nullptr)
			{
				FSaveData& aData = character->SerializedData.Add(i);
				aData = *sData;
			}
		}
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Green, "Loaded: " + CurrentSaveSlot);
}

void USaveManager::DeleteSlot(const FString& slot)
{
	//Delete the slot
	UGameplayStatics::DeleteGameInSlot(slot, 0);

	//Loading the metadata file
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0));
	saveGameMetadata->SavedGamesMetadata.Remove(slot);

	//Save the metadata slot
	UGameplayStatics::SaveGameToSlot(saveGameMetadata, KMetadataSaveSlot, 0);
}

FString USaveManager::GetNewSaveSlot(bool& slot_found)
{
	slot_found = false;

	//Loading the metadata file
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0));

	for (int32 i = 0; i < kMaxSaveSlot; ++i)
	{
		//SaveSlot 0, SaveSlot 1, SaveSlot 2, etc...
		FString slotName = "Save slot " + FString::FromInt(i);

		if (saveGameMetadata->SavedGamesMetadata.Contains(slotName) == false)
		{
			//We found a free slot! Return it
			slot_found = true;
			return slotName;
		}
	}
	return FString();
}

void USaveManager::SetCurrentSaveslot(const FString& slot)
{
	CurrentSaveSlot = slot;
}

FString USaveManager::GetCurrentSaveSlot()
{
	return CurrentSaveSlot;
}

TArray<FSaveMetadata> USaveManager::GetAllSaveMetadata()
{
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSaveMetadata> metadata;

	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0));

	metadata.Reserve(saveGameMetadata->SavedGamesMetadata.Num());

	//Add each saved game's metadata to the return array
	for (const auto saved_game : saveGameMetadata->SavedGamesMetadata)
	{
		metadata.Push(saved_game.Value);
	}
	return metadata;
}

FString USaveManager::GetCurrentMapForLoad(const FString slotName)
{
	USaveGameMetadata* saveGameMetadata = Cast<USaveGameMetadata>(UGameplayStatics::LoadGameFromSlot(KMetadataSaveSlot, 0));

	FSaveMetadata* metadata = saveGameMetadata->SavedGamesMetadata.Find(slotName);

	if (metadata != nullptr)
		return metadata->MapName;

	return FString();
}
