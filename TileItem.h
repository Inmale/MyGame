#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "TileItem.generated.h"

USTRUCT(BlueprintType)
struct FTileItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	int x;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
	int y;
};