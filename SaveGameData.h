// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemParameters.h"
#include "ItemsMetadata.h"
#include "QuestParameters.h"
#include "NoteParameters.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameData.generated.h"

USTRUCT()
struct FSaveData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TArray<uint8> Data;
};
/**
 * 
 */
UCLASS()
class MYGAMEPROTOTYPE_API USaveGameData : public USaveGame
{
	GENERATED_BODY()
protected:
	//Sets activity dialog
	UPROPERTY(VisibleAnywhere)
	TMap<int, bool> activeDialogs;

	//List for containers
	UPROPERTY(VisibleAnywhere)
	TMap<FString, FItemsMetadata> containersList;

	//List of items for maps, which can be saved
	UPROPERTY(VisibleAnywhere)
	TMap<FString, FItemsMetadata> savedMapsList;

	//The list of items for the inventory
	UPROPERTY(VisibleAnywhere)
	TArray<FItemParameters> saveitems;

	//Array of quests
	UPROPERTY(VisibleAnywhere)
	TArray<FQuestParameters> quests;

	//Actors which are overlapped of Player 
	TArray<AActor*> overlappedItems;

	//List of persones and notes
	UPROPERTY(VisibleAnywhere)
	TArray<FNoteParameters> notes;

	//Set if player saw tutorial
	UPROPERTY(VisibleAnywhere)
	bool isSawTutorial;

	//Time
	UPROPERTY(VisibleAnywhere)
	float worldTime = 50000;
public:
	UPROPERTY(VisibleAnywhere)
	TMap<FString, FSaveData> SerializedData;

	TArray<FItemParameters>& GetSaveItems();

	void SetSaveItems(TArray<FItemParameters>& it);

	TMap<FString, FItemsMetadata>& GetItemsMetadata();

	void SetItemsMetadata(TMap<FString, FItemsMetadata>& it);

	void SetQuest(TArray<FQuestParameters>& arr);

	TArray<FQuestParameters>& GetQuests();

	float& GetWorldTime();

	void SetWorldTime(float& time);

	TArray<FNoteParameters>& GetAllNotes();

	void SetNotes(TArray<FNoteParameters>& arr);

	TMap<FString, FItemsMetadata>& GetContMetadata();

	void SetContMetadata(TMap<FString, FItemsMetadata>& it);

	TArray<AActor*>& GetSavedOverActors();

	void SetSavedOverActors(TArray<AActor*>& actors);

	bool GetIsSawTutorial();

	void SetIsSawTutorial(const bool i);

	TMap<int, bool>& GetActiveDialogs();

	void SetActiveDialogs(TMap<int, bool>& i);
};
