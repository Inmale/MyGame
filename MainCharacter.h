// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemParameters.h"
#include "ItemsMetadata.h"
#include "QuestParameters.h"
#include "Engine/SceneCapture2D.h"
#include "NoteParameters.h"
#include "Engine.h"
#include "SaveGameData.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class MYGAMEPROTOTYPE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringMap");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* Minimap = CreateDefaultSubobject<USceneCaptureComponent2D>("Minimap");
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Dialogs")
	TMap<int, bool> activeDialogs;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//List for containers
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Containers")
	TMap<FString, FItemsMetadata> containersList;

	//The array of with quests
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character quests")
	TArray<FQuestParameters> quests;

	//Array items of the inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character inventory")
	TArray<FItemParameters> items;

	//List of items for the each maps
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Metadata Save Items")
	TMap<FString, FItemsMetadata> mapsList;

	//List of persones and notes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character notes")
	TArray<FNoteParameters> notes;

	//Actors which are overlapped of Player 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Overlapped items")
	TArray<AActor*> overlappedItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tutorial")
	bool isSawTutorial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "World time")
	float worldTime = 50000;

public:	

	UPROPERTY(VisibleAnywhere)
	TMap<FString, FSaveData> SerializedData;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Get array inventory
	UFUNCTION(BlueprintPure, Category = "Character inventory")
	UPARAM(DisplayName = "ArrIt") TArray<FItemParameters>& GetItems();

	//Set array inventory for save
	UFUNCTION(BlueprintCallable, Category = "Character inventory")
	void SetItems(const TArray<FItemParameters>& it);

	UFUNCTION(BlueprintPure, Category = "Item save list")
	UPARAM(DisplayName = "Arr") TMap<FString, FItemsMetadata>& GetList();

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void SetList(const TMap<FString, FItemsMetadata>& it);
	//////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void AddItemInDeletedArr(const FString mapName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void RemoveItemInDeleteArr(const FString mapName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void AddItemInAddedArr(const FString mapName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void RemoveItemInAddedArr(const FString mapName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	bool FindItemInDeleteArr(const FString mapName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	bool FindItemInAddedArr(const FString mapName, const FItemParameters param);
	/////////////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "Item save list")
	UPARAM(DisplayName = "Name") FString GetCurrentMapName();

	UFUNCTION(BlueprintCallable, Category = "Item save list")
	void SetAllCoordinatesForObjects(const FItemParameters par, const FVector coord, FRotator rot);

	UFUNCTION(BlueprintPure, Category = "Item save list")
	UPARAM(DisplayName = "Arr") TArray<FItemParameters>	GetDeleteArrayForCurrentMap();

	UFUNCTION(BlueprintPure, Category = "Item save list")
	UPARAM(DisplayName = "Arr") TArray<FItemParameters>	GetAddedArrayForCurrentMap();
	/////////////////////////////////////////////////////
	//Quests
	UFUNCTION(BlueprintPure, Category = "Quests")
	UPARAM(DisplayName = "Arr") TArray<FQuestParameters>& GetActiveQuests();

	UFUNCTION(BlueprintPure, Category = "Quests")
	UPARAM(DisplayName = "Arr") TArray<FQuestParameters>& GetCompletedQuests();

	void SetQuest(TArray<FQuestParameters>& arr);

	UPARAM(DisplayName = "Arr") TArray<FQuestParameters>& GetAllQuests();

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void AddQuest(const FQuestParameters& quest);

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void CompleteQuest(const FQuestParameters& quest);
	/////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "World time")
	UPARAM(DisplayName = "Time") float& GetWorldTime();

	UFUNCTION(BlueprintCallable, Category = "World time")
	void SetWorldTime(const float time);

	UFUNCTION(BlueprintPure, Category = "Character notes")
	UPARAM(DisplayName = "Persons") TArray<FNoteParameters>& GetAllPersons();

	UFUNCTION(BlueprintPure, Category = "Character notes")
	UPARAM(DisplayName = "Notes") TArray<FNoteParameters>& GetAllNotes();

	TArray<FNoteParameters>& GetAllJornal();

	void SetJornal(TArray<FNoteParameters>& arr);

	UFUNCTION(BlueprintCallable, Category = "Character notes")
	void AddPerson(const FNoteParameters& per);

	UFUNCTION(BlueprintCallable, Category = "Character notes")
	void AddNote(const FNoteParameters& note);
	/////////////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "Containers")
	UPARAM(DisplayName = "Arr") TMap<FString, FItemsMetadata>& GetListContainer();

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void SetListContainer(const TMap<FString, FItemsMetadata>& it);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void AddItemInDeletedArrCon(const FString conName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void RemoveItemInDeleteArrCon(const FString conName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void AddItemInAddedArrCon(const FString conName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void RemoveItemInAddedArrCon(const FString conName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	bool FindItemInDeleteArrCon(const FString conName, const FItemParameters param);

	UFUNCTION(BlueprintCallable, Category = "Containers")
	bool FindItemInAddedArrCon(const FString conName, const FItemParameters param);
	////////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "Overlapped items")
	UPARAM(DisplayName = "Actors")TArray<AActor*>& GetSavedOverActors();
	
	UFUNCTION(BlueprintCallable, Category = "Overlapped items")
	void SetSavedOverActors(TArray<AActor*>& actors);
	///////////////////////////////////////////////////

	UFUNCTION(BlueprintPure, Category = "Tutorial")
	UPARAM(DisplayName = "Value") bool GetIsSawTutorial();

	UFUNCTION(BlueprintCallable, Category = "Containers")
	void SetIsSawTutorial(const bool i);
	//////////////////////////////////////////////////
	UFUNCTION(BlueprintPure, Category = "Dialogs")
	UPARAM(DisplayName = "Dialogs") TMap<int, bool>& GetActiveDialogs();

	UFUNCTION(BlueprintCallable, Category = "Dialogs")
	void SetActiveDialogs(TMap<int, bool>& i);

	UFUNCTION(BlueprintCallable, Category = "Dialogs")
	void SetDialog(const int ID, const bool active);
};	

