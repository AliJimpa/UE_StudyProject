// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDevTV/DungeanEscape/GD_CollectableItem.h"

// Sets default values
AGD_CollectableItem::AGD_CollectableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Collectable");
}

// Called when the game starts or when spawned
void AGD_CollectableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGD_CollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

