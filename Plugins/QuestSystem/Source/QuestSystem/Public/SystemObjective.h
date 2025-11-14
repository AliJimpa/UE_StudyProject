// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "SystemObjective.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class QUESTSYSTEM_API USystemObjective : public UObjective
{
	GENERATED_BODY()


public:
	virtual void ExecuteObjective_Implementation(class AQuest *quest) override;

	UFUNCTION(BlueprintNativeEvent)
	void ExecuteBeginplay();
	
};
