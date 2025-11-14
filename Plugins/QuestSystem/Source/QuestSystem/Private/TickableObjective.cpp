// Fill out your copyright notice in the Description page of Project Settings.

#include "TickableObjective.h"

void UTickableObjective::Tick(float DeltaTime)
{
	if (bIsTickable)
	{
		if (Duration != -1)
		{
			timer += DeltaTime;
			if (timer < Duration)
			{
				ReceiveTick(DeltaTime);
			}
			else
			{
				ReceiveFinishTick(DeltaTime);
				bIsTickable = false;
			}
		}else{
			ReceiveTick(DeltaTime);
		}
	}

	UWorld *MyWorld = GetWorld();
	if (MyWorld)
	{
		FLatentActionManager &LatentActionManager = MyWorld->GetLatentActionManager();
		LatentActionManager.ProcessLatentActions(this, MyWorld->GetDeltaSeconds());
	}
}

bool UTickableObjective::IsTickable() const
{
	return bIsTickable;
}

bool UTickableObjective::IsTickableInEditor() const
{
	return false;
}

bool UTickableObjective::IsTickableWhenPaused() const
{
	return false;
}

TStatId UTickableObjective::GetStatId() const
{
	return TStatId();
}

UWorld *UTickableObjective::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UTickableObjective::AllowedToTick(bool setTickable)
{
	bIsTickable = setTickable;
	timer = 0.0f;
}

void UTickableObjective::ExecuteObjective_Implementation(class AQuest *quest)
{
	Super::ExecuteObjective_Implementation(quest);
}
