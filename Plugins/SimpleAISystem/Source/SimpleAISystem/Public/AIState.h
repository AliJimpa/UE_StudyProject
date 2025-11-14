// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIState.generated.h"

UENUM(Blueprintable, BlueprintType)
enum EStateType
{
	OFF,
	SingleState,
	FSM,
	StateCycle,
	Behavior,
};

UENUM(Blueprintable, BlueprintType)
enum EStateMode
{
	None,
	Success,
	Failed,
	Switch,

};

UENUM(Blueprintable, BlueprintType)
enum EDebugtypeA
{
	Information,
	Warning,
	Error,
	Update,
	CoreSystem,
};
/**
 *
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFinishState, uint8, Status);

UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class SIMPLEAISYSTEM_API UAIState : public UObject
{
	GENERATED_BODY()

public:
	virtual void ConstructState(class AAICharacter *Owner);
	void BeginState(int ID, EStateType Type);
	uint8 BehaviorSystem(FString Message);

	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	TSubclassOf<UAISense> GetSenseClass(FAIStimulus AIStimulus);
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	UWorld *GetWorld() const override;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	AAICharacter *GetMyCharacter() const;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	UBlackboardComponent *GetBoard() const;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	bool IsEnable() const;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	int GetMyID() const;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	EStateType GetMyType() const;
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	FString GetTextID() const;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "PrintLog"), Category = "AISystem|State")
	void PrintLog(FString Message, EDebugtypeA type);
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	void FinishState(bool Success);
	UFUNCTION(BlueprintCallable, Category = "AISystem|State")
	void FinishStateSwitch(int Switchindex);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Construct"), Category = "AISystem|State")
	void RecentConstruct();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "BeginState"), Category = "AISystem|State")
	void RecentBeginState();
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TickState"), Category = "AISystem|State")
	void RecentTickState(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "FinishState"), Category = "AISystem|State")
	void RecentFinishState(bool ResetMode);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Behavior"), Category = "AISystem|State")
	uint8 RecentBehavior();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AISystem|State")
	bool IsTickable = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AISystem|State")
	bool hasBlackBoard = true;

	UPROPERTY(BlueprintAssignable, Category = "AISystem|State")
	FFinishState Finish;

private:
	FString TextID = "";
	UBlackboardComponent *MyBlackboard;
	AAICharacter *MyCharacter;
	int MyID;
	EStateType MyType;
	bool IsStateEnable = false;
};
