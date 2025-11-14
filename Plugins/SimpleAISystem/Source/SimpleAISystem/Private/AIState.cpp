// Fill out your copyright notice in the Description page of Project Settings.

#include "AIState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "AICharacter.h"

void UAIState::ConstructState(AAICharacter *Owner)
{
    MyCharacter = Owner;
    MyBlackboard = MyCharacter->FindComponentByClass<UBlackboardComponent>();
    if (!MyBlackboard && hasBlackBoard)
        PrintLog("Your Character Does not have Blackboard Component", EDebugtypeA::CoreSystem);

    RecentConstruct();
}

void UAIState::BeginState(int ID, EStateType Type)
{
    MyID = ID;
    MyType = Type;
    IsStateEnable = true;
    RecentBeginState();
}

uint8 UAIState::BehaviorSystem(FString Message)
{
    MyID = -100;
    MyType = EStateType::Behavior;
    TextID = Message;
    return RecentBehavior();
}

UWorld *UAIState::GetWorld() const
{
    return GetOuter()->GetWorld();
}

TSubclassOf<UAISense> UAIState::GetSenseClass(FAIStimulus AIStimulus)
{
    class UAIPerceptionComponent *PerceptionComponent = MyCharacter->GetController()->FindComponentByClass<UAIPerceptionComponent>();
    if (PerceptionComponent)
    {
        class UAISenseConfig* Config = PerceptionComponent->GetSenseConfig(AIStimulus.Type);
        return Config->GetSenseImplementation();
    }else{
        PrintLog("Your Character Does not have Blackboard Component", EDebugtypeA::CoreSystem);
        return nullptr;
    }
}

    AAICharacter *UAIState::GetMyCharacter() const
    {
        return MyCharacter;
    }

    UBlackboardComponent *UAIState::GetBoard() const
    {
        if (hasBlackBoard)
        {
            if (MyBlackboard)
            {
                return MyBlackboard;
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return nullptr;
        }
    }

    bool UAIState::IsEnable() const
    {
        return IsStateEnable;
    }

    int UAIState::GetMyID() const
    {
        return MyID;
    }

    EStateType UAIState::GetMyType() const
    {
        return MyType;
    }

    FString UAIState::GetTextID() const
    {
        return TextID;
    }

    void UAIState::PrintLog(FString Message, EDebugtypeA type)
    {
        if (MyCharacter)
        {
            MyCharacter->PrintDebug(Message, UKismetSystemLibrary::GetDisplayName(this), type);
        }
    }

    void UAIState::FinishState(bool Success)
    {
        if (MyCharacter)
        {
            if (Success)
            {
                IsStateEnable = false;
                MyCharacter->FinishState(MyID, 1, MyType);
                Finish.Broadcast(1);
            }
            else
            {
                IsStateEnable = false;
                MyCharacter->FinishState(MyID, 2, MyType);
                Finish.Broadcast(2);
            }
        }
    }

    void UAIState::FinishStateSwitch(int Switchindex)
    {
        int index = Switchindex + 3;
        if (MyCharacter)
        {
            IsStateEnable = false;
            MyCharacter->FinishState(MyID, index, MyType);
            Finish.Broadcast(index);
        }
    }
