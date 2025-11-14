// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIState.h"
#include "AIStateMachine.h"
#include "AICharacter.generated.h"

UCLASS()
class SIMPLEAISYSTEM_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void PrintDebug(FString Message, FString Objective, EDebugtypeA type);
	void FinishState(int StateID, uint8 Status, EStateType Type);

	bool FindState(TSubclassOf<UAIState> TargetState);
	UAIState *CreateState(TSubclassOf<UAIState> Class);

	void CallFSMFunction(int State , int Connection);

	UFUNCTION(BLueprintNativeEvent)
	void WarmUpCompleted();

	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void CleanCycleState(int StateID);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AISystem|AICharacter")
	uint8 GetStatusStateCycle(int StateID);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	EStateType GetAISystemType() const ;
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	int CheckCycleStateValid(int StateID);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void ConfigStateCycle(TSubclassOf<UAIState> State, int StateID);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	uint8 ConfigBehavior(TSubclassOf<UAIState> State , FString Text);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void PrintLog(FString Message, EDebugtypeA type);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	UAIState *RunState(TSubclassOf<UAIState> ClassState, bool ResetLastState);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void RunStateCycle(bool ResetLastState);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void RunFSM(UAIStateMachine *FSM, bool ResetLastState);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void RunBehavior(bool ResetLastState);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	void StopAISystem(bool ResetLastState);
	UFUNCTION(BlueprintCallable, Category = "AISystem|AICharacter")
	UAIState* GetCurrentState() const;


	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Behavior"), Category = "AISystem|AICharacter")
	void RecentBehavior();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StateCycle"), Category = "AISystem|AICharacter")
	void RecentStateCycle();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FinishState"), Category = "AISystem|AICharacter")
	void RecentFinishState(int StateID, EStateType Type);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FinishFSM"), Category = "AISystem|AICharacter")
	void RecentFinishFSM(FName Name);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AISystem|AICharacter")
	int NumberOfCycleStates = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AISystem|AICharacter")
	bool Debug = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AISystem|AICharacter")
	bool DebugCoreSystem = false;

private:
	EStateType SystemType;

	UPROPERTY()
	UAIState *CurrentState;
	UPROPERTY()
	TArray<uint8> CycleStates;
	UPROPERTY()
	TArray<UAIState *> Stateslist;
	UPROPERTY()
	UAIStateMachine *Machine;
};
