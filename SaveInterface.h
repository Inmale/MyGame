// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYGAMEPROTOTYPE_API ISaveInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Save Interface")
	FString GetUniqueSaveName();

	UFUNCTION(BlueprintNativeEvent, Category = "Save Interface")
	void OnBeforeSave();
};
