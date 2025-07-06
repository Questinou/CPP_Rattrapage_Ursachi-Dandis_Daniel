// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlagManager.h"
#include "CPP_rattrapageGameMode.generated.h"

UCLASS(minimalapi)
class ACPP_rattrapageGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPP_rattrapageGameMode();

	UFUNCTION(BlueprintCallable, Category = "Flag")
	UFlagManager* GetFlagManager() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flag", meta = (AllowPrivateAccess = "true"))
	UFlagManager* mFlagManager;
};



