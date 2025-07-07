// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact.h"
#include "FlagTrigger.h"
#include <Components/TimelineComponent.h>
#include "Door.generated.h"

UCLASS()
class CPP_RATTRAPAGE_API ADoor : public AActor, public IInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FString GetDescription();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FVector GetUiPosition();

	void Interact_Implementation() override;
	FString GetDescription_Implementation() override;
	FVector GetUiPosition_Implementation() override;

private:
	UFUNCTION()
	void RotateDoors(float time);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UFlagTrigger* FlagTrigger;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UCurveFloat* mCurve;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	float mAnimationDuration;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mDoorLeft;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mSerrureLeft;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mDoorRight;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mSerrureRight;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "RotationAnchor", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mAnchorDoorLeft;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "RotationAnchor", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mAnchorDoorRight;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "RotationAmount", meta = (AllowPrivateAccess = "true"))
	float mLeftRotationDegrees = -45.f;
	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "RotationAmount", meta = (AllowPrivateAccess = "true"))
	float mRightRotationDegrees = -45.f;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	USceneComponent* mUiPosition;

	UTimelineComponent* mTimeline;
	FOnTimelineFloat mCallback{};
	FRotator mInitialRotationLeft;
	FRotator mInitialRotationRight;


	bool mIsOpen;
	bool mKey1Inserted;
	bool mKey0Inserted;
};
