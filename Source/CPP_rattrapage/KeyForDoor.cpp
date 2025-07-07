// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyForDoor.h"
#include "Engine/Engine.h"

// Sets default values
AKeyForDoor::AKeyForDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		cubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (cubeVisualAsset.Succeeded())
	{
		mMesh->SetStaticMesh(cubeVisualAsset.Object);
	}

	mUiPosition = CreateDefaultSubobject<USceneComponent>(TEXT("UI Position"));
	mUiPosition->SetupAttachment(RootComponent);
	mInitialPosition = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AKeyForDoor::BeginPlay()
{
	Super::BeginPlay();
	if (mMaterialList.Num() >= KeyID)
	{
		mMesh->SetMaterial(0, mMaterialList[KeyID]);
	}
}

// Called every frame
void AKeyForDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKeyForDoor::Interact_Implementation()
{
	UFlagManager* FlagManager = nullptr;
	//va chercher Gamemode puis va chercher le flag manager
	UFlagManager* FlagManager = Cast<ACPP_rattrapageGameMode>(GetWorld()->GetAuthGameMode())->GetFlagManager();
	const FString FlagName = FString::Printf(TEXT("KEY_%d"), KeyID);
	FlagManager->ActivateFlag(TEXT("Door"), FlagName);
	Destroy();
}

FString AKeyForDoor::GetDescription_Implementation()
{
	//ID prend la place de %D et permet de ne pas avoir de problème de type ou de saut de ligne tout ça grace à Printf
	return FString::Printf(TEXT("Ramasser la cle %d"), KeyID);
}

FVector AKeyForDoor::GetUiPosition_Implementation()
{
	return mUiPosition->GetComponentLocation();
}



