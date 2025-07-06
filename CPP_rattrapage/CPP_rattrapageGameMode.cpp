// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPP_rattrapageGameMode.h"
#include "CPP_rattrapageCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACPP_rattrapageGameMode::ACPP_rattrapageGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	mFlagManager = CreateDefaultSubobject<UFlagManager>(TEXT("Flag Manager"));
}

UFlagManager* ACPP_rattrapageGameMode::GetFlagManager() const
{
	return mFlagManager;
}
