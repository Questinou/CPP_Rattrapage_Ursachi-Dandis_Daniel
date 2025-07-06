// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	mAnchorDoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnchorDoorLeft"));
	mAnchorDoorLeft->SetupAttachment(RootComponent);
	mAnchorDoorLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mAnchorDoorLeft->bHiddenInGame = true;
	mAnchorDoorLeft->SetWorldScale3D(FVector(0.1f));

	mAnchorDoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AnchorDoorRight"));
	mAnchorDoorRight->SetupAttachment(RootComponent);
	mAnchorDoorRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mAnchorDoorRight->bHiddenInGame = true;
	mAnchorDoorRight->SetWorldScale3D(FVector(0.1f));

	mDoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	mDoorLeft->SetupAttachment(mAnchorDoorLeft);

	mSerrureLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SerrureLeft"));
	mSerrureLeft->SetupAttachment(mDoorLeft);

	mDoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	mDoorRight->SetupAttachment(mAnchorDoorRight);

	mSerrureRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SerrureRight"));
	mSerrureRight->SetupAttachment(mDoorRight);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		cubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (cubeVisualAsset.Succeeded())
	{
		mDoorRight->SetStaticMesh(cubeVisualAsset.Object);
		mSerrureRight->SetStaticMesh(cubeVisualAsset.Object);
		mDoorLeft->SetStaticMesh(cubeVisualAsset.Object);
		mSerrureLeft->SetStaticMesh(cubeVisualAsset.Object);
		mAnchorDoorLeft->SetStaticMesh(cubeVisualAsset.Object);
		mAnchorDoorRight->SetStaticMesh(cubeVisualAsset.Object);
	}

	FlagTrigger = CreateDefaultSubobject<UFlagTrigger>("Flag Trigger");

	mUiPosition = CreateDefaultSubobject<USceneComponent>("UI Position");
	mUiPosition->SetupAttachment(RootComponent);

	mTimeline = CreateDefaultSubobject<UTimelineComponent>("Timeline");

	mCallback.BindUFunction(this, FName{ TEXT("RotateDoors") });
	mInitialRotationLeft = FRotator::ZeroRotator;
	mInitialRotationRight = FRotator::ZeroRotator;
	mIsOpen = false;
	mKey1Inserted=false;
	mKey0Inserted=false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	mTimeline->AddInterpFloat(mCurve, mCallback);
	//if (mAnimationDuration > 0.f)
	//{
	//	mTimeline->SetPlayRate(1.f / mAnimationDuration);
	//}
	mInitialRotationLeft = mAnchorDoorLeft->GetComponentRotation();
	mInitialRotationRight = mAnchorDoorRight->GetComponentRotation();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::Interact_Implementation()
{
	if (mIsOpen)
		return;
	if (!mKey0Inserted && FlagTrigger->IsKeyTriggered(TEXT("Door"),TEXT("KEY_0")))
	{
		mKey0Inserted=true;
		return;
	}
	else if (!mKey1Inserted && FlagTrigger->IsKeyTriggered(TEXT("Door"), TEXT("KEY_1")))
	{
		mKey1Inserted = true;
		return;
	}
	else if (FlagTrigger->IsTriggered())
	{
		mTimeline->Play();
		mIsOpen = true;
	}
}

FString ADoor::GetDescription_Implementation()
{
	if (mIsOpen)
		return TEXT("");
	if (!FlagTrigger->IsKeyTriggered(TEXT("Door"), TEXT("KEY_0")) && !mKey1Inserted && FlagTrigger->IsKeyTriggered(TEXT("Door"), TEXT("KEY_1")))
		return TEXT("Pas de cle");
	

	if (!mKey0Inserted && FlagTrigger->IsKeyTriggered(TEXT("Door"), TEXT("KEY_0"))) 
		return TEXT("Inserer la premiere cle");
	

	if (!mKey1Inserted && FlagTrigger->IsKeyTriggered(TEXT("Door"), TEXT("KEY_1"))) 
		return TEXT("Inserer la deuxieme cle");
	
	
	if (mKey0Inserted && mKey1Inserted)
		return TEXT("Ouvrir");
	return TEXT("");
}

FVector ADoor::GetUiPosition_Implementation()
{
	return mUiPosition->GetComponentLocation();
}

void ADoor::RotateDoors(float time)
{
	FRotator rotationLeft = FMath::Lerp(mInitialRotationLeft, FRotator(0.f, mLeftRotationDegrees,0.f), time);
	FRotator rotationRight = FMath::Lerp(mInitialRotationRight, FRotator(0.f, mRightRotationDegrees, 0.f), time);
	mAnchorDoorLeft->SetRelativeRotation(rotationLeft);
	mAnchorDoorRight->SetRelativeRotation(rotationRight);
}


