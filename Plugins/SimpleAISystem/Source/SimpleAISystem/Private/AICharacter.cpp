// Fill out your copyright notice in the Description page of Project Settings.

#include "AICharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	CycleStates.Empty();
	for (int i = 0; i <= NumberOfCycleStates; ++i)
	{
		CycleStates.Add(0);
	}
	WarmUpCompleted();
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SystemType == EStateType::Behavior)
	{
		RecentBehavior();
	}
	else
	{
		if (CurrentState)
		{
			if (CurrentState->IsTickable)
				CurrentState->RecentTickState(DeltaTime);
		}
	}
}

void AAICharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAICharacter::PrintLog(FString Message, EDebugtypeA type)
{
	PrintDebug(Message, this->GetName(), type);
}

void AAICharacter::WarmUpCompleted_Implementation()
{
	FString newmessage = "states warmed up --> " + FString::Printf(TEXT("%d"), CycleStates.Num());
	PrintLog(newmessage, EDebugtypeA::CoreSystem);
}

UAIState *AAICharacter::RunState(TSubclassOf<UAIState> ClassState, bool ResetLastState)
{
	SystemType = EStateType::SingleState;
	if (ResetLastState)
	{
		if (CurrentState)
		{
			CurrentState->RecentFinishState(true);
			RecentFinishState(CurrentState->GetMyID(), CurrentState->GetMyType());
		}
		else
		{
			PrintLog("Can't Reset: YourState does not valid", EDebugtypeA::CoreSystem);
		}
	}

	if (FindState(ClassState))
	{
		CurrentState->BeginState(-1, EStateType::SingleState);
	}
	else
	{
		CurrentState = CreateState(ClassState);
		CurrentState->ConstructState(this);
		CurrentState->BeginState(-1, EStateType::SingleState);
	}

	return CurrentState;
}

void AAICharacter::RunStateCycle(bool ResetLastState)
{
	SystemType = EStateType::StateCycle;
	if (ResetLastState)
	{
		if (CurrentState)
		{
			CurrentState->RecentFinishState(true);
			RecentFinishState(CurrentState->GetMyID(), CurrentState->GetMyType());
		}
		else
		{
			PrintLog("Can't Reset: YourState does not valid", EDebugtypeA::CoreSystem);
		}
	}
	RecentStateCycle();
}

void AAICharacter::RunFSM(UAIStateMachine *FSM, bool ResetLastState)
{
	if (!FSM)
	{
		PrintLog("FSM File Is not Valid", EDebugtypeA::CoreSystem);
		return;
	}

	SystemType = EStateType::FSM;

	if (ResetLastState)
	{
		if (CurrentState)
		{
			CurrentState->RecentFinishState(true);
			RecentFinishState(CurrentState->GetMyID(), CurrentState->GetMyType());
		}
		else
		{
			PrintLog("Can't Reset: YourState does not valid", EDebugtypeA::CoreSystem);
		}
	}

	if (FSM->IsStableState())
	{
		Machine = FSM;
		FStateMachineData FSMData = FSM->GetFirstState();

		if (FindState(FSMData.StateClass))
		{
			CurrentState->BeginState(FSM->Starter, EStateType::FSM);
		}
		else
		{
			CurrentState = CreateState(FSMData.StateClass);
			CurrentState->ConstructState(this);
			CurrentState->BeginState(FSM->Starter, EStateType::FSM);
		}
	}
	else
	{
		PrintLog("FSM File is not Stable", EDebugtypeA::CoreSystem);
	}
}

void AAICharacter::RunBehavior(bool ResetLastState)
{
	if (ResetLastState)
	{
		if (CurrentState)
		{
			CurrentState->RecentFinishState(true);
			RecentFinishState(CurrentState->GetMyID(), CurrentState->GetMyType());
		}
		else
		{
			PrintLog("Can't Reset: YourState does not valid", EDebugtypeA::CoreSystem);
		}
	}
	SystemType = EStateType::Behavior;
}

void AAICharacter::StopAISystem(bool ResetLastState)
{
	if (ResetLastState)
	{
		if (CurrentState)
		{
			CurrentState->RecentFinishState(true);
			RecentFinishState(CurrentState->GetMyID(), CurrentState->GetMyType());
		}
		else
		{
			PrintLog("Can't Reset: YourState does not valid", EDebugtypeA::CoreSystem);
		}
	}
	SystemType = EStateType::OFF;
	CurrentState = nullptr;
}

void AAICharacter::PrintDebug(FString Message, FString Objective, EDebugtypeA type)
{
	FColor messagecolor;
	float delay = 10;
	switch (type)
	{
	case EDebugtypeA::Information:
		messagecolor = FColor::White;
		delay = 5;
		break;
	case EDebugtypeA::Warning:
		messagecolor = FColor::Yellow;
		break;
	case EDebugtypeA::Error:
		messagecolor = FColor::Red;
		break;
	case EDebugtypeA::Update:
		messagecolor = FColor::Blue;
		delay = 0.005;
		break;
	case EDebugtypeA::CoreSystem:
		messagecolor = FColor::Black;
		delay = 5;
		break;
	}
	if (EDebugtypeA::CoreSystem == type)
	{
		if (DebugCoreSystem)
		{
			//GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor, FString::Printf(TEXT("[%s :: %s] : %s"), *GetController()->GetName(), *Objective, *Message));
		}
	}
	else
	{
		if (Debug)
		{
			//GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor, FString::Printf(TEXT("[%s :: %s] : %s"), *GetController()->GetName(), *Objective, *Message));
		}
	}
}

int AAICharacter::CheckCycleStateValid(int StateID)
{
	if (StateID >= 0)
	{
		if (CycleStates.IsValidIndex(StateID))
		{
			return StateID;
		}
		else
		{
			FString newmessage = "State ID Is Not Valid --> " + FString::Printf(TEXT("%d"), StateID);
			PrintLog(newmessage, EDebugtypeA::CoreSystem);
			return 0;
		}
	}
	else
	{
		FString newmessage = "Your ID State is Wrong_ " + FString::Printf(TEXT("%d"), StateID);
		PrintLog(newmessage, EDebugtypeA::CoreSystem);
		return 0;
	}
}

void AAICharacter::ConfigStateCycle(TSubclassOf<UAIState> State, int StateID)
{
	if (FindState(State))
	{
		CurrentState->BeginState(StateID, EStateType::StateCycle);
	}
	else
	{
		CurrentState = CreateState(State);
		CurrentState->ConstructState(this);
		CurrentState->BeginState(StateID, EStateType::StateCycle);
	}
}

uint8 AAICharacter::ConfigBehavior(TSubclassOf<UAIState> State, FString Text)
{
	if (FindState(State))
	{
		return CurrentState->BehaviorSystem(Text);
	}
	else
	{
		CurrentState = CreateState(State);
		CurrentState->ConstructState(this);
		return CurrentState->BehaviorSystem(Text);
	}
}

UAIState *AAICharacter::CreateState(TSubclassOf<UAIState> Class)
{
	UAIState *NewState = Cast<UAIState>(UGameplayStatics::SpawnObject(Class, this));
	Stateslist.Add(NewState);
	return NewState;
}

void AAICharacter::CallFSMFunction(int State, int Connection)
{
	FString CodeName = FString::Printf(TEXT("%d"), State) + "_" + FString::Printf(TEXT("%d"), Connection);

	if (Machine->FunctionLibrary.Contains(CodeName))
	{
		UFunction *Function = this->FindFunction( Machine->FunctionLibrary[CodeName] );
		if (Function)
		{
			// If the function is found, you can call it
			this->ProcessEvent(Function, nullptr);
		}
		else
		{
			// Handle the case where the function is not found
			PrintLog("There is not any function in class", EDebugtypeA::CoreSystem);

		}
	}
	
}

bool AAICharacter::FindState(TSubclassOf<UAIState> TargetState)
{
	bool findstate = false;
	for (const auto &state : Stateslist)
	{
		if (state->GetClass() == TargetState)
		{
			CurrentState = state;
			findstate = true;
		}
	}
	return findstate;
}

uint8 AAICharacter::GetStatusStateCycle(int StateID)
{
	if (CycleStates.IsValidIndex(StateID))
	{
		return CycleStates[StateID];
	}
	else
	{
		FString newmessage = "there isnt any state with this ID_ " + FString::Printf(TEXT("%d"), StateID);
		PrintLog(newmessage, EDebugtypeA::CoreSystem);
		return 0;
	}
}

EStateType AAICharacter::GetAISystemType() const
{
	return SystemType;
}

void AAICharacter::CleanCycleState(int StateID)
{
	if (CycleStates.IsValidIndex(StateID))
	{
		CycleStates[StateID] = 0;
	}
	else
	{
		FString newmessage = "there isnt any state with this ID_" + FString::Printf(TEXT("%d"), StateID);
		PrintLog(newmessage, EDebugtypeA::CoreSystem);
	}
}

UAIState *AAICharacter::GetCurrentState() const
{
	return CurrentState;
}

void AAICharacter::FinishState(int StateID, uint8 Status, EStateType Type)
{
	switch (Type)
	{
	case EStateType::SingleState:
		if (CurrentState)
		{
			CurrentState->RecentFinishState(false);
		}
		break;
	case EStateType::StateCycle:
		if (CycleStates.IsValidIndex(StateID))
		{
			if (CurrentState)
			{
				CurrentState->RecentFinishState(false);
			}
			CycleStates[StateID] = Status;
			RecentStateCycle();
		}
		else
		{
			FString newmessage = "Cant Finish State With this ID -> " + FString::Printf(TEXT("%d"), StateID);
			PrintLog(newmessage, EDebugtypeA::CoreSystem);
		}
		break;
	case EStateType::FSM:
		if (CurrentState)
		{
			CurrentState->RecentFinishState(false);
		}

		if (Machine->GetConnectionIndex(StateID, Status) == -1)
		{
			RecentFinishFSM(Machine->FileName);
			return;
		}
		if (Machine->GetConnectionIndex(StateID, Status) == -2)
		{
			PrintLog("FSM File Have Problem", EDebugtypeA::CoreSystem);
			return;
		}
		if (Machine->GetConnectionIndex(StateID, Status) == -99)
		{
			PrintLog("Your State Is Not Valid", EDebugtypeA::CoreSystem);
			return;
		}
		if (Machine->GetConnectionIndex(StateID, Status) == -100)
		{
			PrintLog("There is no defined for this section", EDebugtypeA::CoreSystem);
			return;
		}

		TSubclassOf<UAIState> newstateclass = Machine->GetStateClass(Machine->GetConnectionIndex(StateID, Status));

		if (FindState(newstateclass))
		{
			CallFSMFunction(StateID , Status-1);
			CurrentState->BeginState(Machine->GetConnectionIndex(StateID, Status), EStateType::FSM);
		}
		else
		{
			CurrentState = CreateState(newstateclass);
			CurrentState->ConstructState(this);
			CallFSMFunction(StateID , Status-1);
			CurrentState->BeginState(Machine->GetConnectionIndex(StateID, Status), EStateType::FSM);
		}
		break;
	}
	RecentFinishState(StateID, Type);
}
