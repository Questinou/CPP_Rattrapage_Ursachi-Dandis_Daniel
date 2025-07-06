// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Flag.h"
#include "FlagCategory.h"
#include "FlagManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFlagValueChanged);

UCLASS()
class CPP_RATTRAPAGE_API UFlagManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UFlagManager();

	UFUNCTION(BlueprintCallable, Category = "Flag")
	void ActivateFlag(const FString& category, const FString& flagName);

	UFUNCTION(BlueprintCallable, Category = "Flag")
	bool IsFlagValid(const FString& category, const FString& flagName) const;

	UFUNCTION(BlueprintCallable, Category = "Flag")
	bool IsFlagTriggered(const FFlag& flag) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString GetFlagKey(const FString& category, const FString& flagName) const;

public:
	FFlagValueChanged OnFlagTriggered;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	TArray<FFlagCategory> FlagsList;

private:
	TMap<FString, FFlag> mFlags;
};
