#pragma once

#include "Runtime/CoreUObject/Public/UObject/Class.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInterface.h"
#include "ItemParameters.generated.h"

USTRUCT(BlueprintType)
struct FItemParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString unuqueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FIntPoint dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UMaterialInterface* icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<AStaticMeshActor> class_ob;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	int ID_Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FVector location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool mustBeDeleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FRotator rotatorObj;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FString infoIsDontKnow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool IsKnow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool canSteal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool crime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	ACharacter* Owner;
};