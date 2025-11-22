// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDevTV/DungeanEscape/GD_BoxTrigger.h"
#include "GD_BoxTrigger.h"

UGD_BoxTrigger::UGD_BoxTrigger()
{
    PrimaryComponentTick.bCanEverTick = false;

    OnComponentBeginOverlap.AddDynamic(this, &UGD_BoxTrigger::OnOverlapBegin); // set up a notification for when this component overlaps something
    OnComponentEndOverlap.AddDynamic(this, &UGD_BoxTrigger::OnOverlapEnd);     // set up a notification for when this component overlaps something

    UE_LOG(LogTemp, Display, TEXT("Trigger Constructed"));
}

void UGD_BoxTrigger::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Trigger Begin"));
    if (TargetDoor != nullptr)
    {
        DoorMover = TargetDoor->FindComponentByClass<UGD_Mover>();
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Door Not Selected"));
    }
}

void UGD_BoxTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UE_LOG(LogTemp, Display, TEXT("Trigger Tick!"));
}

void UGD_BoxTrigger::SetTigger(bool enable)
{
    isTrigger = enable;
    if (DoorMover)
    {
        DoorMover->ShouldMove = isTrigger;
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("The Door Should have Mover Component"));
    }
}

void UGD_BoxTrigger::OnOverlapBegin(UPrimitiveComponent *OverlappedComp,
                                    AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (!OtherActor->ActorHasTag(BeginTag))
        return;

    OberlapCount++;
    SetTigger(true);
}

void UGD_BoxTrigger::OnOverlapEnd(UPrimitiveComponent *OverlappedComp,
                                  AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor->ActorHasTag(EndTag))
        return;
    OberlapCount--;
    if (OberlapCount == 0)
        SetTigger(false);
}
