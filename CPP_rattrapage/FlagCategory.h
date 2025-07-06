// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlagCategory.generated.h"

USTRUCT(BlueprintType)
struct FFlagCategory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
	FString Category;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flag")
	TArray<FString> FlagsNames;
};
