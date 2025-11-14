// Fill out your copyright notice in the Description page of Project Settings.

#include "ACCoreTask.h"
#include "AICoreRuntime/Base/ACController.h"
#include "AICoreRuntime/Tasks/ACTaskManager.h"
#include "Kismet/GameplayStatics.h"


void UACCoreTask::CreateTask(UACController* Controller, UObject* Owner)
{
    MyController = Controller;
    MyOwner = Owner;
}

void UACCoreTask::StartTask(UObject* Starter)
{

}

void UACCoreTask::UpdateTask(float DeltaTime)
{
    if (TargetTask)
        TargetTask->UpdateTask(DeltaTime);
}

void UACCoreTask::EndTask(UObject* Terminator , ETaskDoneType Type , int EndIndex)
{
    switch (Type)
    {
    case ETaskDoneType::Self:
        if (MyOwner)
        {
            UACTaskManager* MyManager = Cast<UACTaskManager>(MyOwner);
            if (MyManager)
                MyManager->AnyTaskDone(this , EndIndex);
        }
        break;
    case ETaskDoneType::Other:
        /* code */
        break;
    }
}

void UACCoreTask::RunTask(TSubclassOf<UACCoreTask> Target)
{
    TargetTask = Cast<UACCoreTask>(UGameplayStatics::SpawnObject(Target, this));
        if (TargetTask)
        {
            TargetTask->CreateTask(MyController , this);
            TargetTask->StartTask(this);
        }
            
}
