// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyActor.h"

// Sets default values
AStudyActor::AStudyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStudyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Display,TEXT("Hallolee"));
	UE_LOG(LogTemp,Display,TEXT("Hallolee"));
	
}

// Called every frame
void AStudyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

