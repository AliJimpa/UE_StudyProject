// Fill out your copyright notice in the Description page of Project Settings.


#include "AILocator.h"

// Sets default values
AAILocator::AAILocator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAILocator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAILocator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAILocator::SetActorTitle(FString name)
{
#if WITH_EDITOR
	this->SetActorLabel(name, true);
#endif
}

