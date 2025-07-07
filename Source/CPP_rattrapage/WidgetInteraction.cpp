// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetInteraction.h"

void UWidgetInteraction::SetDescription(const FString& description)
{
	mDescriptionBlock->SetText(FText::FromString(description));
}

void UWidgetInteraction::SetPosition(const FVector2D& position)
{
	Cast<UCanvasPanelSlot>(mDescriptionBlock->Slot)->SetPosition(position);
}

void UWidgetInteraction::NativeConstruct()
{
	mDescriptionBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")));
	if (mDescriptionBlock == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Interraction widget : text block not found"));
	}
}
