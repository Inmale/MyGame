#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "NoteParameters.generated.h"

USTRUCT(BlueprintType)
struct FNoteParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool isHuman;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int ID;
};