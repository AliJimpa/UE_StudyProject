// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ACTask.h"
#include "ACTickableTask.generated.h"


/**
 *
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class AICORERUNTIME_API UACTickableTask : public UACTask, public FTickableGameObject
{
	GENERATED_BODY()

public:
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;
	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;
	UWorld *GetWorld() const override;

private:
	bool bIsTickable;
	float timer;

	// Blueprint Layer Implementation
protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"),Category = "AICore|TickableTask")
	void ReceiveTick(float DeltaSeconds);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FinishTick"),Category = "AICore|TickableTask")
	void ReceiveFinishTick(float DeltaSeconds);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly , meta = (AllowPrivateAccess = "true") ,Category = "AICore|TickableTask")
	float Duration;
	UFUNCTION(BlueprintCallable,meta = (AllowPrivateAccess = "true" ),Category = "AICore|TickableTask")
	void AllowedToTick(bool setTickable);
	UFUNCTION(BlueprintCallable,meta = (AllowPrivateAccess = "true"),Category = "AICore|TickableTask")
	void AllowedToTickWithDuration(bool setTickable , float setDuration);
};
