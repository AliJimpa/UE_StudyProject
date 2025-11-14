// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Objective.generated.h"


UENUM(Blueprintable,BlueprintType)
enum EDebugtype
{
	Information,
	Warning,
	Error,
	Update,
	CoreSystem,
};
UENUM(Blueprintable,BlueprintType)
enum Eexutetype
{
	NextObjective,
	PreviousObjective,
	TargetObjective,
	EndObjective,
	StartObjective,
};
/**
 *
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class QUESTSYSTEM_API UObjective : public UObject
{
	GENERATED_BODY()

public:
	void RunObjective(class AQuest *quest, FString Name);

protected:

	UFUNCTION(BlueprintNativeEvent)
	void ExecuteObjective(class AQuest *quest);

	void NativeExecute();

	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	void ExcObjective(Eexutetype Run , FString Target);
	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	void ExcObjectiveIndex(int Index);
	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	void Debug(FString Message, EDebugtype type);
	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	bool IsExcute() const;
	UFUNCTION(BlueprintCallable, Category ="QuestSystem|Objective")
	void FinishObjective();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="QuestSystem")
	bool CallbackQuest = true;
	

private:

	class AQuest *MyOwner;
	FString MyName;
	bool bIsExcute = false;


};
