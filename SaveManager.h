// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveMetadata.h"
#include "SaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "SaveManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MYGAMEPROTOTYPE_API USaveManager : public UObject
{
	GENERATED_BODY()
private:
	//The current save clot
	static FString CurrentSaveSlot;

	//All the actors in the game which implement the save interface
	static TArray<TScriptInterface<ISaveInterface>> SaveInterfaces;

public:

	//Initialize the class. Must called when the game first launches
	static void Init();

	//Queries all actors in the game that implement the save interface
	static void QueryAllSaveInterfaces();

	//Saves the current state of the game
	UFUNCTION(BlueprintCallable, Category = "Saving and Loading")
	static void SaveGame();

	//Load the current game
	UFUNCTION(BlueprintCallable, Category = "Saving and Loading")
	static void LoadGame();

	//Delete the specified slot
	UFUNCTION(BlueprintCallable, Category = "Saving and Loading")
	static void DeleteSlot(const FString& slot);

	//Gets a new, unused slot
	UFUNCTION(BlueprintPure, Category = "Saving and Loading")
	static UPARAM(DisplayName = "Slot") FString GetNewSaveSlot(bool& slot_found);

	//Sets the current save slot to the specified value
	UFUNCTION(BlueprintCallable, Category = "Saving and Loading")
	static void SetCurrentSaveslot(const FString& slot);

	//Gets the current save slot to the spesified value
	UFUNCTION(BlueprintPure, Category = "Saving and Loading")
	static FString GetCurrentSaveSlot();

	//Gets all the saved games
	UFUNCTION(BlueprintPure, Category = "Saving and Loading")
	static TArray<FSaveMetadata> GetAllSaveMetadata();

	//Gets map name from save slot
	UFUNCTION(BlueprintCallable, Category = "Saving and Loading")
	static UPARAM(DisplayName = "MapName") FString GetCurrentMapForLoad(const FString slotName);
};
