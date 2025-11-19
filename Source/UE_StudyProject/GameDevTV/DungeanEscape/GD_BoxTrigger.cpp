// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDevTV/DungeanEscape/GD_BoxTrigger.h"
#include "GD_BoxTrigger.h"

UGD_BoxTrigger::UGD_BoxTrigger()
{
    PrimaryComponentTick.bCanEverTick = false;
    UE_LOG(LogTemp, Display, TEXT("Trigger Constructed"));
}

void UGD_BoxTrigger::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Trigger Begin"));
}

void UGD_BoxTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UE_LOG(LogTemp, Display, TEXT("Trigger Tick!"));
}
