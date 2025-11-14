// Fill out your copyright notice in the Description page of Project Settings.


#include "TickableCommand.h"

void UTickableCommand::Tick(float DeltaTime)
{
	if (bIsTickable)
	{
		timer += DeltaTime;
		if(timer < Duration)
		{
			ReceiveTick(DeltaTime);
		}else{
			ReceiveFinishTick(DeltaTime);
			bIsTickable = false;
		}
		
	}

	UWorld* MyWorld = GetWorld();
	if (MyWorld)
	{
		FLatentActionManager& LatentActionManager = MyWorld->GetLatentActionManager();
		LatentActionManager.ProcessLatentActions(this, MyWorld->GetDeltaSeconds());
	}
}

bool UTickableCommand::IsTickable() const
{
	return bIsTickable;
}

bool UTickableCommand::IsTickableInEditor() const
{
	return false;
}

bool UTickableCommand::IsTickableWhenPaused() const
{
	return false;
}

TStatId UTickableCommand::GetStatId() const
{
	return TStatId();
}

UWorld* UTickableCommand::GetWorld() const
{
	return GetOuter()->GetWorld();
}

void UTickableCommand::AllowedToTick(bool setTickable)
{
	bIsTickable = setTickable;
	timer = 0.0f;

}

void UTickableCommand::Execute_Implementation(class AActor* Owner , class AActor* Parent ,class UPrimitiveComponent *OverlappedComp ,const FHitResult &SweepResult)
{
	Super::Execute_Implementation(Owner,Parent,OverlappedComp,SweepResult);
	AllowedToTick(true);
}
