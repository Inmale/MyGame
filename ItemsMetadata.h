#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "ItemParameters.h"
#include "ItemsMetadata.generated.h"

USTRUCT(BlueprintType)
struct FItemsMetadata
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FItemParameters> addedItems;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
		TArray<FItemParameters> removedItems;
};