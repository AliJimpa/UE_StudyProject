// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICoreRuntime/Tasks/ACTask.h"
#include "ACTaskManager.generated.h"

/**
 * 
 */
UCLASS()
class AICORERUNTIME_API UACTaskManager : public UACTask
{
	GENERATED_BODY()

public:

	virtual void AnyTaskDone(UACCoreTask* Task , int FinishIndex);
	
};
