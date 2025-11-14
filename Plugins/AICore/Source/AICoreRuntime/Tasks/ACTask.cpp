// Fill out your copyright notice in the Description page of Project Settings.


#include "ACTask.h"

void UACTask::CreateTask(UACController* Controller, UObject* Owner)
{
    Super::CreateTask(Controller,Owner);
    RecentCreate(Owner);
}

void UACTask::StartTask(UObject* Starter)
{
    Super::StartTask(Starter);
    RecentStartTask();
}

void UACTask::UpdateTask(float DeltaTime)
{
    RecentUpdateTask(DeltaTime);
}

void UACTask::EndTask(UObject* Terminator , ETaskDoneType Type , int EndIndex)
{
    OnTaskDone.Broadcast(Terminator , Type , EndIndex);
    RecentEndTask();
    Super::EndTask(Terminator , Type , EndIndex);
}

void UACTask::FinishTask(int Index)
{
    EndTask(this, ETaskDoneType::Self , Index);
}