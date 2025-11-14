// Fill out your copyright notice in the Description page of Project Settings.

#include "Objective.h"
#include "Quest.h"

void UObjective::RunObjective(AQuest *quest, FString Name)
{
    MyOwner = quest;
    MyName = Name;
    bIsExcute = true;
    ExecuteObjective(MyOwner);

    if (CallbackQuest)
    {
        if (MyOwner)
        {
            MyOwner->ReceiveObjective(MyName);
        }else{
            Debug("Quest Owner Not Valid",EDebugtype::CoreSystem);
        }
        
        
    }

    if (!MyOwner)
    {
        Debug("Quest Owner Not Valid",EDebugtype::CoreSystem);
    }
    
    
}

void UObjective::ExecuteObjective_Implementation(AQuest *quest)
{
    Debug("You have to Use Excute Event",EDebugtype::CoreSystem);
}

void UObjective::NativeExecute()
{
    
}

void UObjective::ExcObjective(Eexutetype Run , FString Target)
{
    if (MyOwner)
    {
        MyOwner->MachineObjective(Run, Target);
    }else{
        Debug("Quest Owner Not Valid",EDebugtype::CoreSystem);
    }
}

void UObjective::ExcObjectiveIndex(int Index)
{
    if (MyOwner)
    {
        MyOwner->RunObjectiveIndex(Index);
    }else{
        Debug("Quest Owner Not Valid",EDebugtype::CoreSystem);
    }
}

void UObjective::Debug(FString Message, EDebugtype type)
{
    if (MyOwner)
    {
        MyOwner->PrintDebug(Message , MyName ,type);
    }
}

bool UObjective::IsExcute() const
{
    return bIsExcute;
}

void UObjective::FinishObjective()
{
    ExcObjective(Eexutetype::NextObjective , "");
}
