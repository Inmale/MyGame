// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

TArray<FQuestParameters> activeQuests;
TArray<FQuestParameters> completedQuests;

TArray<FNoteParameters> people;
TArray<FNoteParameters> notesList;

bool operator==(const FNoteParameters& left, const FNoteParameters right)
{
	return left.ID == right.ID;
}

bool operator==(const FItemParameters& left, const FItemParameters& right)
{
	return left.ID_Item == right.ID_Item;
}

bool operator==(const FQuestParameters& left, const FQuestParameters& right)
{
	return left.questID == right.questID;
}

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp->SetupAttachment(GetMesh());

	Minimap->SetupAttachment(SpringArmComp);

	Minimap->ShowFlags.SkeletalMeshes = 0;
	Minimap->ShowFlags.Atmosphere = 0;
	Minimap->ShowFlags.DynamicShadows = 0;
}
// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<FItemParameters>& AMainCharacter::GetItems()
{
	return AMainCharacter::items;
}

void AMainCharacter::SetItems(const TArray<FItemParameters>& it)
{
	AMainCharacter::items.Empty();
	if (!it.IsEmpty())
	{
		for (auto& item : it)
		{
			items.Add(item);
		}
	}
}

TMap<FString, FItemsMetadata>& AMainCharacter::GetList()
{
	return mapsList;
}

void AMainCharacter::SetList(const TMap<FString, FItemsMetadata>& it)
{
	AMainCharacter::mapsList.Empty();
	if (!it.IsEmpty())
	{
		for (auto& i : it)
		{
			mapsList.Add(i);
		}
	}
}

void AMainCharacter::AddItemInDeletedArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata& item = mapsList.FindOrAdd(mapName);
	item.removedItems.Add(param);
}

void AMainCharacter::RemoveItemInDeleteArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata* item = mapsList.Find(mapName);
	if (item != nullptr)
	{
		item->removedItems.Remove(param);
	}
}

void AMainCharacter::AddItemInAddedArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata& item = mapsList.FindOrAdd(mapName);
	item.addedItems.Add(param);
}

void AMainCharacter::RemoveItemInAddedArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata* item = mapsList.Find(mapName);
	if (item != nullptr)
	{
		item->addedItems.Remove(param);
	}
}

bool AMainCharacter::FindItemInDeleteArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata* meta = mapsList.Find(mapName);
	if (meta == nullptr)
		return false;
	return meta->removedItems.Contains(param);
}

bool AMainCharacter::FindItemInAddedArr(const FString mapName, const FItemParameters param)
{
	FItemsMetadata* meta = mapsList.Find(mapName);
	if (meta == nullptr)
		return false;
	return meta->addedItems.Contains(param);
}

FString AMainCharacter::GetCurrentMapName()
{
	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	return LevelName;
}

void AMainCharacter::SetAllCoordinatesForObjects(const FItemParameters par, const FVector coord, FRotator rot)
{
	FString nameMap = AMainCharacter::GetCurrentMapName();
	FItemsMetadata& meta = mapsList.FindOrAdd(nameMap);
	int position = meta.addedItems.Find(par);
	if (position != INDEX_NONE)
	{
		meta.addedItems[position].location = coord;
		meta.addedItems[position].rotatorObj = rot;
	}
	else
	{
		position = meta.removedItems.Find(par);
		if (position != INDEX_NONE)
		{
			meta.removedItems[position].location = coord;
			meta.removedItems[position].rotatorObj = rot;
		}
		else
		{
			position = meta.removedItems.Add(par);
			meta.removedItems[position].location = coord;
			meta.removedItems[position].rotatorObj = rot;
		}
	}
}

TArray<FItemParameters> AMainCharacter::GetDeleteArrayForCurrentMap()
{
	FString nameMap = AMainCharacter::GetCurrentMapName();
	FItemsMetadata* meta = mapsList.Find(nameMap);
	if (meta == nullptr)
		return TArray<FItemParameters>();
	return meta->removedItems;
}

TArray<FItemParameters> AMainCharacter::GetAddedArrayForCurrentMap()
{
	FString nameMap = AMainCharacter::GetCurrentMapName();
	FItemsMetadata* meta = mapsList.Find(nameMap);
	if (meta == nullptr)
		return TArray<FItemParameters>();
	return meta->addedItems;
}

//Quests
TArray<FQuestParameters>& AMainCharacter::GetActiveQuests()
{
	activeQuests.Empty();
	for (auto& i : quests)
	{
		if (i.questCompleted == false)
		{
			activeQuests.Add(i);
		}
	}
	return activeQuests;
}

TArray<FQuestParameters>& AMainCharacter::GetCompletedQuests()
{
	completedQuests.Empty();
	for (auto& i : quests)
	{
		if (i.questCompleted == true)
		{
			completedQuests.Add(i);
		}
	}
	return completedQuests;
}

void AMainCharacter::SetQuest(TArray<FQuestParameters>& arr)
{
	AMainCharacter::quests.Empty();
	if (!arr.IsEmpty())
	{
		for (auto& i : arr)
		{
			quests.Add(i);
		}
	}
}

TArray<FQuestParameters>& AMainCharacter::GetAllQuests()
{
	return AMainCharacter::quests;
}

void AMainCharacter::AddQuest(const FQuestParameters& quest)
{
	int pos = AMainCharacter::quests.Find(quest);
	if (pos == INDEX_NONE)
	{
		pos = AMainCharacter::quests.Add(quest);
		quests[pos].questCompleted = false;
	}
	else
	{
		if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, "Error. Quest has added: " + quest.nameQuest);
	}
}

void AMainCharacter::CompleteQuest(const FQuestParameters& quest)
{
	int pos = AMainCharacter::quests.Find(quest);
	if (pos != INDEX_NONE)
	{
		quests[pos].questCompleted = true;
	}
	else
	{
		if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, "Error. Completed quest not found: " + quest.nameQuest);
	}
}

UPARAM(DisplayName = "Time") float& AMainCharacter::GetWorldTime()
{
	return AMainCharacter::worldTime;
}

void AMainCharacter::SetWorldTime(const float time)
{
	AMainCharacter::worldTime = time;
}

TArray<FNoteParameters>& AMainCharacter::GetAllPersons()
{
	people.Empty();
	for (auto& i : AMainCharacter::notes)
	{
		if (i.isHuman)
		{
			people.Add(i);
		}
	}
	return people;
}

TArray<FNoteParameters>& AMainCharacter::GetAllNotes()
{
	notesList.Empty();
	for (auto& i : AMainCharacter::notes)
	{
		if (!i.isHuman)
		{
			notesList.Add(i);
		}
	}
	return notesList;
}

TArray<FNoteParameters>& AMainCharacter::GetAllJornal()
{
	return AMainCharacter::notes;
}

void AMainCharacter::SetJornal(TArray<FNoteParameters>& arr)
{
	AMainCharacter::notes.Empty();
	if (!arr.IsEmpty())
	{
		for (auto& i : arr)
		{
			AMainCharacter::notes.Add(i);
		}
	}
}

void AMainCharacter::AddPerson(const FNoteParameters& per)
{
	int pos = AMainCharacter::notes.Find(per);
	if (pos == INDEX_NONE)
	{
		pos = AMainCharacter::notes.Add(per);
		notes[pos].isHuman = true;
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, "Error. Person has added: " + per.name);
	}
}

void AMainCharacter::AddNote(const FNoteParameters& note)
{
	int pos = AMainCharacter::notes.Find(note);
	if (pos == INDEX_NONE)
	{
		pos = AMainCharacter::notes.Add(note);
		notes[pos].isHuman = false;
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Red, "Error. Note has added: " + note.name);
	}
}

TMap<FString, FItemsMetadata>& AMainCharacter::GetListContainer()
{
	return AMainCharacter::containersList;
}

void AMainCharacter::SetListContainer(const TMap<FString, FItemsMetadata>& it)
{
	AMainCharacter::containersList.Empty();
	if (!it.IsEmpty())
	{
		for (auto& i : it)
		{
			AMainCharacter::containersList.Add(i);
		}
	}
}

void AMainCharacter::AddItemInDeletedArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata& item = AMainCharacter::containersList.FindOrAdd(conName);
	item.removedItems.Add(param);
}

void AMainCharacter::RemoveItemInDeleteArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata* item = AMainCharacter::containersList.Find(conName);
	if (item != nullptr)
	{
		item->removedItems.Remove(param);
	}
}

void AMainCharacter::AddItemInAddedArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata& item = AMainCharacter::containersList.FindOrAdd(conName);
	item.addedItems.Add(param);
}

void AMainCharacter::RemoveItemInAddedArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata* item = AMainCharacter::containersList.Find(conName);
	if (item != nullptr)
	{
		item->addedItems.Remove(param);
	}
}

bool AMainCharacter::FindItemInDeleteArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata* meta = AMainCharacter::containersList.Find(conName);
	if(meta == nullptr)
		return false;
	return meta->removedItems.Contains(param);
}

bool AMainCharacter::FindItemInAddedArrCon(const FString conName, const FItemParameters param)
{
	FItemsMetadata* meta = AMainCharacter::containersList.Find(conName);
	if (meta == nullptr)
		return false;
	return meta->addedItems.Contains(param);
}

TArray<AActor*>& AMainCharacter::GetSavedOverActors()
{
	return AMainCharacter::overlappedItems;
}

void AMainCharacter::SetSavedOverActors(TArray<AActor*>& actors)
{
	AMainCharacter::overlappedItems.Empty();
	for (auto& i : actors)
	{
		if (i != nullptr)
		{
			AMainCharacter::overlappedItems.Add(i);
		}
	}
}

bool AMainCharacter::GetIsSawTutorial()
{
	return AMainCharacter::isSawTutorial;
}

void AMainCharacter::SetIsSawTutorial(const bool i)
{
	AMainCharacter::isSawTutorial = i;
}

TMap<int, bool>& AMainCharacter::GetActiveDialogs()
{
	return AMainCharacter::activeDialogs;
}

void AMainCharacter::SetActiveDialogs(TMap<int, bool>& i)
{
	AMainCharacter::activeDialogs.Empty();
	if (!i.IsEmpty())
	{
		for (auto& n : i)
		{
			AMainCharacter::activeDialogs.Add(n);
		}
	}
}

void AMainCharacter::SetDialog(const int ID = 0, const bool active = false)
{
		auto& d = AMainCharacter::activeDialogs.FindOrAdd(ID);
		d = active;
}
