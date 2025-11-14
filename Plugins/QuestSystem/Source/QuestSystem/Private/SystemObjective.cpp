// Fill out your copyright notice in the Description page of Project Settings.


#include "SystemObjective.h"

void USystemObjective::ExecuteObjective_Implementation(class AQuest *quest)
{
	Super::ExecuteObjective_Implementation(quest);
}

void USystemObjective::ExecuteBeginplay_Implementation()
{
    Debug("You have to Use BeginPlay Event",EDebugtype::CoreSystem);
}

