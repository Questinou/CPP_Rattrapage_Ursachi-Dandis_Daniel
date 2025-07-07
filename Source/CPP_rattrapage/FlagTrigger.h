// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_rattrapageGameMode.h"
#include "FlagTrigger.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_RATTRAPAGE_API UFlagTrigger : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UFlagTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Callback")
	void InvokeIfTriggered();
	UFUNCTION(BlueprintCallable, Category = "Callback")
	bool IsTriggered();
	bool IsKeyTriggered(const FString& category, const FString& flagName);

private:
	void CheckFlagValidity();

public:
	UPROPERTY(BlueprintAssignable)
	FFlagValueChanged OnFlagTriggered;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	TArray<FFlag> Flags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flags")
	bool bListen = false;

private:
	UFlagManager* mFlagManager;
};
