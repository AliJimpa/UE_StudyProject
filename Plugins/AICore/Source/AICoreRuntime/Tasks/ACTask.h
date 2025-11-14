// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICoreRuntime/Core/ACCoreTask.h"
#include "ACTask.generated.h"

/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FTaskDone, UObject *, Refrence,  ETaskDoneType, Type , int , Index);

UCLASS(Abstract, Blueprintable, BlueprintType)
class AICORERUNTIME_API UACTask : public UACCoreTask
{
	GENERATED_BODY()

public:
	virtual void CreateTask(UACController *Controller, UObject *Owner) override;
	virtual void StartTask(UObject *Starter) override;
	virtual void UpdateTask(float DeltaTime) override;
	virtual void EndTask(UObject* Terminator , ETaskDoneType Type , int EndIndex) override;

	//** Blueprint Layer Implementation **
public:
	// Delegate for ending Task
	UPROPERTY(BlueprintAssignable, Category = "AICore|Task")
	FTaskDone OnTaskDone;

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "CreateTask"), Category = "AICore|Task")
	void RecentCreate(UObject *Owner);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StartTask"), Category = "AICore|Task")
	void RecentStartTask();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "UpdateTask"), Category = "AICore|Task")
	void RecentUpdateTask(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EndTask"), Category = "AICore|Task")
	void RecentEndTask();
private:
	UFUNCTION(BlueprintCallable ,meta = (AllowPrivateAccess = "true") , Category = "AICore|Task")
	void FinishTask(int Index);
};
