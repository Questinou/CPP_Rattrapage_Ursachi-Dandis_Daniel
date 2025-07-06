// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>
#include "WidgetInteraction.generated.h"

UCLASS()
class CPP_RATTRAPAGE_API UWidgetInteraction : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDescription(const FString& description);
	void SetPosition(const FVector2D& position);

protected:
	virtual void NativeConstruct() override;

private:
	UTextBlock* mDescriptionBlock;
};

