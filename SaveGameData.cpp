// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameData.h"

TArray<FItemParameters>& USaveGameData::GetSaveItems()
{
    return USaveGameData::saveitems;
}

void USaveGameData::SetSaveItems(TArray<FItemParameters>& items)
{
    USaveGameData::saveitems.Empty();

    if (!items.IsEmpty())
    {
        for (auto& it : items)
        {
            saveitems.Add(it);
        }
    }
}

TMap<FString, FItemsMetadata>& USaveGameData::GetItemsMetadata()
{
    return USaveGameData::savedMapsList;
}

void USaveGameData::SetItemsMetadata(TMap<FString, FItemsMetadata>& it)
{
    USaveGameData::savedMapsList.Empty();
    if (!it.IsEmpty())
    {
        for (auto& i : it)
        {
            savedMapsList.Add(i);
        }
    }
}

void USaveGameData::SetQuest(TArray<FQuestParameters>& arr)
{
    USaveGameData::quests.Empty();
    if (!arr.IsEmpty())
    {
        for (auto& i: arr)
        {
            quests.Add(i);
        }
    }
}

TArray<FQuestParameters>& USaveGameData::GetQuests()
{
    return USaveGameData::quests;
}

float& USaveGameData::GetWorldTime()
{
    return USaveGameData::worldTime;
}

void USaveGameData::SetWorldTime(float& time)
{
    USaveGameData::worldTime = time;
}

TArray<FNoteParameters>& USaveGameData::GetAllNotes()
{
    return USaveGameData::notes;
}

void USaveGameData::SetNotes(TArray<FNoteParameters>& arr)
{
    USaveGameData::notes.Empty();
    if (!arr.IsEmpty())
    {
        for (auto& i : arr)
        {
            USaveGameData::notes.Add(i);
        }
    }
}

TMap<FString, FItemsMetadata>& USaveGameData::GetContMetadata()
{
    return USaveGameData::containersList;
}

void USaveGameData::SetContMetadata(TMap<FString, FItemsMetadata>& it)
{
    USaveGameData::containersList.Empty();
    if (!it.IsEmpty())
    {
        for (auto& i : it)
        {
            containersList.Add(i);
        }
    }
}

TArray<AActor*>& USaveGameData::GetSavedOverActors()
{
    return USaveGameData::overlappedItems;
}

void USaveGameData::SetSavedOverActors(TArray<AActor*>& actors)
{
    USaveGameData::overlappedItems.Empty();
    for (auto& i : actors)
    {
        if (i != nullptr)
        {
            USaveGameData::overlappedItems.Add(i);
        }
    }
}

bool USaveGameData::GetIsSawTutorial()
{
    return USaveGameData::isSawTutorial;
}

void USaveGameData::SetIsSawTutorial(const bool i)
{
    USaveGameData::isSawTutorial = i;
}

TMap<int, bool>& USaveGameData::GetActiveDialogs()
{
    return USaveGameData::activeDialogs;
}

void USaveGameData::SetActiveDialogs(TMap<int, bool>& i)
{
    USaveGameData::activeDialogs.Empty();
    if (!i.IsEmpty())
    {
        for (auto& n : i)
        {
            USaveGameData::activeDialogs.Add(n);
        }
    }
}

