// Fill out your copyright notice in the Description page of Project Settings.


#include "FlagManager.h"
#include "Engine/Engine.h"

// Sets default values
UFlagManager::UFlagManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

void UFlagManager::ActivateFlag(const FString& category, const FString& flagName)
{
	const FString key = GetFlagKey(category, flagName);

	if (mFlags.Contains(key))
	{
		mFlags[key].bTooked = true;
		OnFlagTriggered.Broadcast();
	}
}

bool UFlagManager::IsFlagValid(const FString& category, const FString& flagName) const
{
	const FString key = GetFlagKey(category, flagName);
	return mFlags.Contains(key);
}

bool UFlagManager::IsFlagTriggered(const FFlag& Flag) const
{
	const FString key = GetFlagKey(Flag.Category, Flag.FlagName);

	if (!mFlags.Contains(key))
		return false;

	if (Flag.bTooked==true)
		return true;
	return false;
}

// Called when the game starts or when spawned
void UFlagManager::BeginPlay()
{
	Super::BeginPlay();
	
	mFlags = TMap<FString, FFlag>();
	for (const auto& flagList : FlagsList)
	{
		for (const auto& flag : flagList.FlagsNames)
		{
			FString key = GetFlagKey(flagList.Category, flag);
			mFlags.Emplace(key,
				{
					flagList.Category,
					flag,
					false
				});
		}
	}
}

const FString UFlagManager::GetFlagKey(const FString& category, const FString& flagName) const
{
	return category + ":" + flagName;
}


