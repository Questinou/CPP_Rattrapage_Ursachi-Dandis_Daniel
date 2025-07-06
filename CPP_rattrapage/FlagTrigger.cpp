// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagTrigger.h"
#include "Engine/Engine.h"

// Sets default values
UFlagTrigger::UFlagTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

	mFlagManager = nullptr;

}

// Called when the game starts or when spawned
void UFlagTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	mFlagManager = static_cast<ACPP_rattrapageGameMode*>(GetWorld()->GetAuthGameMode())->GetFlagManager();

	FTimerHandle timerHandler;
	GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &UFlagTrigger::CheckFlagValidity, 0.001f, false);

	if (bListen)
		mFlagManager->OnFlagTriggered.AddDynamic(this, &UFlagTrigger::InvokeIfTriggered);
}

void UFlagTrigger::BeginDestroy()
{
	Super::BeginDestroy();

	if (bListen && mFlagManager != nullptr)
		mFlagManager->OnFlagTriggered.RemoveDynamic(this, &UFlagTrigger::InvokeIfTriggered);
}

void UFlagTrigger::CheckFlagValidity()
{
	for (const auto& flag : Flags)
	{
			if (!mFlagManager->IsFlagValid(flag.Category, flag.FlagName))
				UE_LOG(LogTemp, Error, TEXT("%s => flag does not exist."), *(flag.FlagName));
	}
}

void UFlagTrigger::InvokeIfTriggered()
{
	for (const auto& flag : Flags)
	{
		if (!mFlagManager->IsFlagTriggered(flag))
			return;
	}

	OnFlagTriggered.Broadcast();
}

bool UFlagTrigger::IsTriggered()
{
	for (const auto& flag : Flags)
	{
		if (!mFlagManager->IsFlagTriggered(flag))
			return false;
	}

	return true;
}

bool UFlagTrigger::IsKeyTriggered(const FString& category, const FString& flagName)
{
	for (const auto& flag : Flags)
	{
		if (flag.Category==category && flag.FlagName == flagName) 
		{
			if (flag.bTooked) 
			{
				return true;
			}
		}
	}
	return false;
}
