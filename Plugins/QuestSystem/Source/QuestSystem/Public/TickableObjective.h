// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "TickableObjective.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class QUESTSYSTEM_API UTickableObjective : public UObjective, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="QuestSystem")
	float Duration;
	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	void AllowedToTick(bool bIsTickable);

private:
	bool bIsTickable;
	float timer;

public:
	void Tick(float DeltaTime) override;
	bool IsTickable() const override;

	bool IsTickableInEditor() const override;
	bool IsTickableWhenPaused() const override;
	TStatId GetStatId() const override;

	UWorld *GetWorld() const override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Tick"))
	void ReceiveTick(float DeltaSeconds);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FinishTick"))
	void ReceiveFinishTick(float DeltaSeconds);

	

	virtual void ExecuteObjective_Implementation(class AQuest *quest) override;
};
