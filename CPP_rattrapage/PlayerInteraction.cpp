// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteraction.h"

// Sets default values for this component's properties
UPlayerInteraction::UPlayerInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	mCamera = nullptr;
	mInteractionRange = 0.0f;
	mInteractable = nullptr;
}


// Called when the game starts
void UPlayerInteraction::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UPlayerInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	InteractDetection();
}

void UPlayerInteraction::UseInteraction()
{
	if (mInteractable == nullptr)
		return;

	IInteract::Execute_Interact(mInteractable);
}

void UPlayerInteraction::InteractDetection()
{
	FHitResult hit;
	ECollisionChannel channel(ECC_GameTraceChannel1);
	const FCollisionQueryParams traceParam(FName(TEXT("")), false, GetOwner());

	FVector startPosition = mCamera->GetComponentLocation();
	FVector endPosition = startPosition + mCamera->GetForwardVector() * mInteractionRange;

	if (!GetWorld()->LineTraceSingleByChannel(OUT hit, startPosition, endPosition, channel, traceParam))
	{
		mInteractable = nullptr;
		return;
	}

	AActor* hitActor = hit.GetActor();
	if (hitActor == nullptr)
	{
		SetInteractionDescription("");
		mInteractable = nullptr;
		return;
	}

	if (hitActor->GetClass()->ImplementsInterface(UInteract::StaticClass()))
	{
		mInteractable = hitActor;
		FString description = IInteract::Execute_GetDescription(mInteractable);
		SetInteractionDescription(description);
	}
	else
		mInteractable = nullptr;

}

bool UPlayerInteraction::TryGetController()
{
	UWorld* world = GetWorld();
	if (world == nullptr)
		return false;

	mController = world->GetFirstPlayerController();
	if (mController == nullptr)
		return false;
	return true;
}

bool UPlayerInteraction::TryGetHUD()
{
	UWorld* world = GetWorld();
	if (world == nullptr)
		return false;

	APlayerController* controller = world->GetFirstPlayerController();
	if (controller == nullptr)
		return false;

	mHud = Cast<AGameHUD>(controller->GetHUD());
	if (mHud == nullptr)
		return false;

	return true;
}

void UPlayerInteraction::SetInteractionDescription(const FString& description)
{
	if (mHud != nullptr || TryGetHUD())
		mHud->SetInteractionDescription(description);
}

void UPlayerInteraction::SetInteractionPosition()
{
	if (mInteractable == nullptr)
		return;


	if (mController != nullptr || TryGetController())
	{
		FVector worldPosition = IInteract::Execute_GetUiPosition(mInteractable);

		FVector2D uiPosition = FVector2D::ZeroVector;

		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(mController, worldPosition, uiPosition, true);
		if (mHud != nullptr || TryGetHUD())
			mHud->SetInteractionPosition(uiPosition);

	}

}

