// Fill out your copyright notice in the Description page of Project Settings.

#include "AIStateMachine.h"


FStateMachineData UAIStateMachine::GetFirstState() const
{
    return MachineData[Starter];
}

bool UAIStateMachine::IsStableState() const
{
    if (MachineData.Num() >= 2)
    {
        return true;
    }else{
        return false;
    }
    
}

int UAIStateMachine::AddState(TSubclassOf<UAIState> stateclass)
{
    FStateMachineData newData;
    newData.StateClass = stateclass;
    newData.Conections.Add(MachineData.Num());
    return MachineData.Add(newData);
}

bool UAIStateMachine::AddConnection(int StateIndex, int Status, int TargetStateIndex)
{
    if (MachineData.IsValidIndex(StateIndex))
    {
        FStateMachineData newData = MachineData[StateIndex];
        if (newData.Conections.IsValidIndex(Status))
        {
           newData.Conections[Status] = TargetStateIndex;
        }else{
            for (size_t i = newData.Conections.Num(); i < TargetStateIndex; i++)
            {
                newData.Conections.Add(-1);
            }
            newData.Conections[Status] = TargetStateIndex;
        }
        return true;
    }else{
        return false;
    }
}

bool UAIStateMachine::RemoveState(int StateIndex)
{
    if (MachineData.IsValidIndex(StateIndex))
    {
        MachineData.RemoveAt(StateIndex);
        return true;
    }else
    {
        return false;
    }
}

bool UAIStateMachine::RemoveConnection(int StateIndex, int Status)
{
    if (MachineData.IsValidIndex(StateIndex))
    {
        if (MachineData[StateIndex].Conections.IsValidIndex(Status))
        {
            MachineData[StateIndex].Conections.RemoveAt(Status);
            return true;
        }else{
            return false;
        }
    }else
    {
        return false;
    }
}

TSubclassOf<UAIState> UAIStateMachine::GetStateClass(int StateIndex)
{
    if (MachineData.IsValidIndex(StateIndex))
    {
        FStateMachineData newData = MachineData[StateIndex];
        return newData.StateClass;
    }else{
        return nullptr;
    }
    
}

int UAIStateMachine::GetConnectionIndex(int StateIndex, int Status)
{
    if (MachineData.IsValidIndex(StateIndex))
    {
        if (MachineData[StateIndex].Conections.IsValidIndex(Status-1))
        {
            return MachineData[StateIndex].Conections[Status-1];
        }else{
            return -100;
        }
        
    }else{
        return -99;
    }
}
