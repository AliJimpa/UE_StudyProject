// Fill out your copyright notice in the Description page of Project Settings.


#include "ACTickableTask.h"

void UACTickableTask::Tick(float DeltaTime)
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

bool UACTickableTask::IsTickable() const
{
	return bIsTickable;
}

bool UACTickableTask::IsTickableInEditor() const
{
	return false;
}

bool UACTickableTask::IsTickableWhenPaused() const
{
	return false;
}

TStatId UACTickableTask::GetStatId() const
{
	return TStatId();
}

UWorld *UACTickableTask::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UACTickableTask::AllowedToTick(bool setTickable)
{
    timer = 0.0f;
	bIsTickable = setTickable;
}

void UACTickableTask::AllowedToTickWithDuration(bool setTickable , float setDuration)
{
    Duration = setDuration;
    timer = 0.0f;
	bIsTickable = setTickable;
	
}