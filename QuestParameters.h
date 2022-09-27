#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "QuestParameters.generated.h"

USTRUCT(BlueprintType)
struct FQuestParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString nameQuest;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	bool questCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int questID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString activeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString completeText;
};