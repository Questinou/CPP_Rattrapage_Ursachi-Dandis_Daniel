// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact.h"
#include "FlagTrigger.h"
#include "KeyForDoor.generated.h"

UCLASS()
class CPP_RATTRAPAGE_API AKeyForDoor : public AActor , public IInteract
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyForDoor();

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

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mMesh;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	USceneComponent* mUiPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> mMaterialList;

	UPROPERTY(EditAnywhere, BlueprintREADWrite, Category = "ID", meta = (AllowPrivateAccess = "true"))
	int KeyID;

	FVector mInitialPosition;
};
