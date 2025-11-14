// Fill out your copyright notice in the Description page of Project Settings.


#include "Command.h"
#include "CommandTrigger.h"

void UCommand::Execute_Implementation(class AActor* Owner , class AActor* Parent ,class UPrimitiveComponent *OverlappedComp ,const FHitResult &SweepResult)
{

}

void UCommand::NativeExecute()
{
    
}


bool UCommand::Timer(float deltatime ,float Duration)
{
    timer = timer + deltatime;
    if (timer <= Duration)
    {
        return true;
    }else{
        return false;
    }
    
}

float UCommand::GetTimer() const
{
    return timer;
}

void UCommand::ResetTimer()
{
    timer = 0;
}


void UCommand::Debug(class ACommandTrigger* Owner ,FString Message, EDebugtypeC type)
{
   Owner->PrintDebug(Message,this->GetName(),type);
}

void UCommand::FinishCommand()
{

}
