// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ACCoreTask.generated.h"

class UACController;

/**
 *
 */
UENUM(Blueprintable, BlueprintType)
enum ETaskDoneType
{
	Self,
	Other,
};

UCLASS()
class AICORERUNTIME_API UACCoreTask : public UObject
{

	GENERATED_BODY()

public:
	// Call when task create & Set Owner & AIConttroller
	virtual void CreateTask(UACController* Controller , UObject* Owner);
	// Call when task start they job
	virtual void StartTask(UObject* Starter);
	// Call after starting task everyframe
	virtual void UpdateTask(float DeltaTime);
	// Call when task ended by self or managertask
	virtual void EndTask(UObject* Terminator , ETaskDoneType Type , int EndIndex);

	void RunTask(TSubclassOf<UACCoreTask> Target);

private:
	UACController* MyController;
	UObject* MyOwner;
	UACCoreTask* TargetTask;
};
