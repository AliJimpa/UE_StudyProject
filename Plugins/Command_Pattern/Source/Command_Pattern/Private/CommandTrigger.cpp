// Fill out your copyright notice in the Description page of Project Settings.

#include "CommandTrigger.h"
#include "Components/ShapeComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"



ACommandTrigger::ACommandTrigger()
{
    PrimaryActorTick.bCanEverTick = true;
    GetCollisionComponent()->ShapeColor = FColor::Red;
    GetCollisionComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACommandTrigger::OnTriggerBeginOverlap);
    GetCollisionComponent()->OnComponentEndOverlap.AddDynamic(this, &ACommandTrigger::OnTriggerEndOverlap);
}

void ACommandTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void ACommandTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TickUpdate.Broadcast(DeltaTime);

    if (BeginGate && !BeginRunTime)
    {
        if (BeginOverlap.IsValidIndex(BeginIndex))
        {
            const float delaytime = BeginOverlap[BeginIndex].Timeline - BeginTimer;
            if (delaytime >= 0)
            {
                BeginTimer = BeginOverlap[BeginIndex].Timeline;
                PrintDebug("BeginExcuteCommand", "Core",EDebugtypeC::CoreSystem);
                BeginRunTime = true;
            }
            else
            {
                PrintDebug("There is Problem in Begin Timeline", "Core",EDebugtypeC::CoreSystem);
                BeginReset();
            }
        }
        else
        {
            BeginReset();
        }
    }

    if (EndGate && !EndRunTime)
    {
        if (EndOverlap.IsValidIndex(EndIndex))
        {
            const float Edelaytime = EndOverlap[EndIndex].Timeline - EndTimer;
            if (Edelaytime >= 0)
            {
                EndTimer = EndOverlap[EndIndex].Timeline;
                DelayTime("EndExcuteCommand", Edelaytime);
                EndRunTime = true;
            }
            else
            {
                PrintDebug("There is Problem in End Timeline", "Core",EDebugtypeC::CoreSystem);
                EndReset();
            }
        }
        else
        {
            EndReset();
        }
    }

}

void ACommandTrigger::OnTriggerBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    PrintDebug("BeginTrigger", OtherActor->GetName(),EDebugtypeC::CoreSystem);
    if (IsPlayerTag(OtherActor) && !BeginGate)
    {
        BeginActor = OtherActor;
        BeginComp = OverlappedComp;
        BeginHit = SweepResult;
        BeginGate = true;
        PrintDebug("Begin_Cast Player", "Core",EDebugtypeC::CoreSystem);
    }
    else
    {
        PrintDebug("Begin_Cast Player or Faild", "Core",EDebugtypeC::CoreSystem);
    }
}

void ACommandTrigger::OnTriggerEndOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    PrintDebug("EndTrigger", OtherActor->GetName(),EDebugtypeC::CoreSystem);
    if (IsPlayerTag(OtherActor) && !EndGate)
    {
        EndActor = OtherActor;
        EndComp = OverlappedComp;
        EndGate = true;
        PrintDebug("End_Cast Player", "Core",EDebugtypeC::CoreSystem);

    }
    else
    {
        PrintDebug("End_Cast Player or Faild", "Core",EDebugtypeC::CoreSystem);
    }
}

void ACommandTrigger::BeginExcuteCommand()
{
    PrintDebug("Begin_Commands Run", BeginOverlap[BeginIndex].Command->GetName(),EDebugtypeC::CoreSystem);
    BeginOverlap[BeginIndex].Command->Execute(this, BeginActor, BeginComp, BeginHit);
    CommandRun.Broadcast(BeginOverlap[BeginIndex].Command , ExcuteType::BeginOverlap);
    BeginIndex++;
    BeginRunTime = false;
}

void ACommandTrigger::EndExcuteCommand()
{
    PrintDebug("End_Commands Run", "Core",EDebugtypeC::CoreSystem);
    EndOverlap[EndIndex].Command->Execute(this, EndActor, EndComp, EndHit);
    CommandRun.Broadcast(EndOverlap[BeginIndex].Command , ExcuteType::EndOverlap);
    EndIndex++;
    EndRunTime = false;
}

void ACommandTrigger::BeginReset()
{
    BeginIndex = 0;
    BeginTimer = 0;
    BeginGate = false;
    PrintDebug("Reset BeginTrigger", "Core",EDebugtypeC::CoreSystem);
}

void ACommandTrigger::EndReset()
{
    EndIndex = 0;
    EndTimer = 0;
    EndGate = false;
    PrintDebug("Reset EndTrigger", "Core",EDebugtypeC::CoreSystem);
}


void ACommandTrigger::FPlaySound2D( USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency* ConcurrencySettings , const AActor* OwningActor , bool bIsUISound )
{
	UGameplayStatics::PlaySound2D( GetWorld() , Sound , VolumeMultiplier, PitchMultiplier , StartTime , ConcurrencySettings , OwningActor , bIsUISound );
}

void ACommandTrigger::FPlaySoundAtLocation( USoundBase* Sound, FVector Location, float VolumeMultiplier , float PitchMultiplier , float StartTime , class USoundAttenuation* AttenuationSettings , USoundConcurrency* ConcurrencySettings, UInitialActiveSoundParams* InitialParams)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld() , Sound , Location , VolumeMultiplier , PitchMultiplier , StartTime , AttenuationSettings , ConcurrencySettings , InitialParams);
}

AActor* ACommandTrigger::FSpawnActor(UClass* ChildActorClass , FName ChildActorName, FVector const Location , FRotator const Rotation)
{
	
	FActorSpawnParameters Params;
	 //Params.bNoCollisionFail = true;
	 Params.bDeferConstruction = true;
	 Params.bAllowDuringConstructionScript = true;
	 Params.OverrideLevel = GetOwner()->GetLevel();
	 Params.Name = ChildActorName;

    class AActor* NewActor = GetWorld()->SpawnActor(ChildActorClass , &Location,&Rotation , Params);
    ActorBank.Add(NewActor);
	return NewActor;
}

APlayerController* ACommandTrigger::FGetPlayerController(int index) const
{
    return UGameplayStatics::GetPlayerController(GetWorld(),index);
}

ACharacter* ACommandTrigger::FGetPlayerCharacter(int index) const
{
    return UGameplayStatics::GetPlayerCharacter(GetWorld(),index);
}

UUserWidget* ACommandTrigger::FCreateWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    class UUserWidget* createdWidget = CreateWidget<UUserWidget>( GetWorld() , WidgetClass);
	createdWidget->AddToViewport();
    WidgetBank.Add(createdWidget);
    return WidgetBank[0];
}




bool ACommandTrigger::DestroyActorID(int ID)
{
    if (ActorBank.IsValidIndex(ID))
    {
        ActorBank[ID]->K2_DestroyActor();
        ActorBank.RemoveAt(ID);
        return true;
    }else{
        return false;
    }
    
}

bool ACommandTrigger::DestroyWidgetID(int ID)
{
    if (WidgetBank.IsValidIndex(ID))
    {
        WidgetBank[ID]->RemoveFromParent();
        WidgetBank.RemoveAt(ID);
        return true;
    }else{
        return false;
    }
}

AActor* ACommandTrigger::GetActorID(int ID)
{
    return ActorBank[ID];
}

UUserWidget* ACommandTrigger::GetWidgetID(int ID)
{
    return WidgetBank[ID];
}



void ACommandTrigger::DelayTime(FName Methodname, float Time)
{
    FLatentActionInfo action;
    action.ExecutionFunction = Methodname;
    action.CallbackTarget = this;
    action.Linkage = 0;
    action.UUID = 0;
    UKismetSystemLibrary::Delay(this, Time, action);
}

void ACommandTrigger::PrintDebug(FString Message, FString Objective, EDebugtypeC type)
{
    FColor messagecolor = FColor::White;
    float delay = 10;
    switch (type)
    {
    case EDebugtypeC::Information:
        messagecolor = FColor::White;
        break;
    case EDebugtypeC::Warning:
        messagecolor = FColor::Yellow;
        break;
    case EDebugtypeC::Error:
        messagecolor = FColor::Red;
        break;
    case EDebugtypeC::Update:
        messagecolor = FColor::Blue;
        delay = 0.01;
        break;
    case EDebugtypeC::CoreSystem:
        messagecolor = FColor::Black;
        break;
    }
    if (EDebugtypeC::CoreSystem == type)
    {
        if (DebugCoreSystem && GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor, FString::Printf(TEXT("[%s :: %s] : %s"), *this->GetName(), *Objective, *Message));
        }
    }
    else
    {
        if (Debug && GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor, FString::Printf(TEXT("[%s :: %s] : %s"), *this->GetName(), *Objective, *Message));
        }
    }
}

bool ACommandTrigger::IsPlayerTag(AActor* Target) const
{
    bool result = false;
    if (Target->Tags.Num() > 0)
    {
        for (size_t i = 0; i < Target->Tags.Num(); i++)
        {
            if (PlayerTag == Target->Tags[i])
            {
                result = true;
            }
        }
    }
    return result;
}


