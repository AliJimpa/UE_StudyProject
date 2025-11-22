// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDevTV/DungeanEscape/GD_Lock.h"
#include "GD_Lock.h"

// Sets default values
AGD_Lock::AGD_Lock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(root);
	myTrigger = CreateDefaultSubobject<UGD_BoxTrigger>(TEXT("LockTrigger"));
	myTrigger->SetupAttachment(root);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	mesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AGD_Lock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGD_Lock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGD_Lock::SetIsKeyPlaced(bool enable)
{
	isKeyPlaced = enable;
}

bool AGD_Lock::GetIsKeyPlaced()
{
    return isKeyPlaced;
}
