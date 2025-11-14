// Fill out your copyright notice in the Description page of Project Settings.


#include "ACController.h"
#include "Kismet/GameplayStatics.h"
#include "../Core/ACCoreTask.h"



// Sets default values for this component's properties
UACController::UACController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UACController::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//CoreTask = Cast<UACCoreTask>(UGameplayStatics::SpawnObject(MasterTask, this));
	CoreTask = NewObject<UACCoreTask>(this, MasterTask);
	if (CoreTask)
	{
		CoreTask->CreateTask(this , this);
		CoreTask->StartTask(this);
	}
		
	
	
}


// Called every frame
void UACController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (CoreTask)
	{
		CoreTask->UpdateTask(DeltaTime);
	}
}

