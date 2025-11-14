// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

USTRUCT(Blueprintable)
struct FObjectivate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	UObjective *Function;
};

UCLASS()
class QUESTSYSTEM_API AQuest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform &Transform) override;

	UFUNCTION(BlueprintCallable, Category = "QuestSystem|Quest")
	void StartQuest();
	//FUNCTION(BlueprintCallable, Category = "QuestSystem|Quest")
	void EndQuest();
	UFUNCTION(BlueprintCallable, Category = "QuestSystem|Quest")
	void SetEnableQuest(bool Enable);
	UFUNCTION(BlueprintCallable, Category = "QuestSystem|Quest")
	bool GetQuestEnable() const;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExcObjective"), Category = "QuestSystem|Quest")
	void RunObjectiveTarget(FString ObjectiveName);
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MachineObjective(Eexutetype type, FString Target);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Debug"), Category = "QuestSystem|Quest")
	void PrintDebug(FString Message, FString Objective, EDebugtype type);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ExcObjectiveIndex"), Category = "QuestSystem|Quest")
	void RunObjectiveIndex(int index);

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest")
	FString QuestName = "Quest";
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest")
	TArray<FObjectivate> Objectives = TArray<FObjectivate>();
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Quest")
	bool Debug = false;
	UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category = "Quest")
	bool DebugCoreSystem = false;

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StartQuest"), Category = "QuestSystem|Quest")
	void ReceiveStartQuest();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EndQuest"), Category = "QuestSystem|Quest")
	void ReceiveEndQuest();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "EnableQuest"), Category = "QuestSystem|Quest")
	void ReceiveEnableQuest();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "DisableQuest"), Category = "QuestSystem|Quest")
	void ReceiveDisableQuest();

public:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Objective"), Category = "QuestSystem|Quest")
	void ReceiveObjective(const FString &name);

private:
	bool IsQuestEnable = false;
	int ObjectIndex = -1;
	bool FirstStart = false;
	
	void RunObjectives(int index);
	void RefreshQuest();


};
