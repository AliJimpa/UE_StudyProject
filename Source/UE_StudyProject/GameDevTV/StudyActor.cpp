// Fill out your copyright notice in the Description page of Project Settings.

#include "StudyActor.h"

// Sets default values
AStudyActor::AStudyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void TESTLog()
{
	int MyNumber = 199;
	UE_LOG(LogTemp, Display, TEXT("Hallolee"));
	UE_LOG(LogTemp, Display, TEXT("Hallolee %d"), MyNumber);
}

// Called when the game starts or when spawned
void AStudyActor::BeginPlay()
{
	Super::BeginPlay();
	TESTLog();
	startLocation = GetActorLocation();
}

// Called every frame
void AStudyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveActor(DeltaTime);
	RotateActor(DeltaTime);
	
}

float AStudyActor::GetDistanceMoved(FVector currentLoc)
{
	return FVector::Dist(startLocation , currentLoc);
}

void AStudyActor::MoveActor(float deltatime)
{
	// MoveObject
	FVector CurrentPosition = GetActorLocation();
	CurrentPosition = actorVelocity * deltatime + CurrentPosition;
	SetActorLocation(CurrentPosition);

	// Check Distance
	float distanceMoved = GetDistanceMoved(CurrentPosition);
	if(distanceMoved >= moveDistance)
	{
		// solve OverShoot
		float overShoot = distanceMoved - moveDistance;
		FString InstanceName = GetName();
		UE_LOG(LogTemp , Display , TEXT("%s overshoot by %f") , *InstanceName , overShoot);

		FVector MoveDirection = actorVelocity.GetSafeNormal();
		FVector NewStartLocation = startLocation + MoveDirection * moveDistance;
		SetActorLocation(NewStartLocation);
		startLocation = NewStartLocation;
		actorVelocity = -actorVelocity;
	}
}


void AStudyActor::RotateActor(float deltatime)
{
	FRotator RotationToAdd = rotateVelocity * deltatime;
	AddActorLocalRotation(RotationToAdd);
}
