// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "Interact.h"
#include "GameHUD.h"
#include "PlayerInteraction.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_RATTRAPAGE_API UPlayerInteraction : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UFUNCTION(BlueprintCallable)
	void UseInteraction();

	void InteractDetection();

	bool TryGetController();
	bool TryGetHUD();
	void SetInteractionDescription(const FString& description);
	void SetInteractionPosition();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mInteractionRange;

	AActor* mInteractable;

	AGameHUD* mHud;
	APlayerController* mController;
};