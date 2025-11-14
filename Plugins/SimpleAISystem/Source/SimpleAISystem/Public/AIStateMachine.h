// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AIState.h"
#include "AIStateMachine.generated.h"

USTRUCT(BlueprintType)
struct FStateMachineData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	TSubclassOf<UAIState> StateClass;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	TArray<int> Conections;

};
/**
 *
 */
UCLASS()
class SIMPLEAISYSTEM_API UAIStateMachine : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "AISystem|AIStateMachine")
	int AddState(TSubclassOf<UAIState> stateclass);

	UFUNCTION(BlueprintCallable, Category = "AISystem|AIStateMachine")
	bool AddConnection(int StateIndex , int Status , int TargetStateIndex);

	UFUNCTION(BlueprintCallable, Category = "AISystem|AIStateMachine")
	bool RemoveState(int StateIndex);

	UFUNCTION(BlueprintCallable, Category = "AISystem|AIStateMachine")
	bool RemoveConnection(int StateIndex, int Status);

	FStateMachineData GetFirstState() const;
	bool IsStableState() const;
	TSubclassOf<UAIState> GetStateClass(int StateIndex);
	int GetConnectionIndex(int StateIndex , int Status);


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	FName FileName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	int Starter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	TArray<FStateMachineData> MachineData;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AISystem|AIStateMachine")
	TMap<FString, FName> FunctionLibrary;
};
