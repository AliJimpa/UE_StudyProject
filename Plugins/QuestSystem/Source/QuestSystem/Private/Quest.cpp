// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest.h"
#include "SystemObjective.h"

// Sets default values
AQuest::AQuest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();

	FirstStart = IsQuestEnable;

	if (IsQuestEnable)
	{
		for (const auto &obj : Objectives)
		{
			if (obj.Function)
			{
				class USystemObjective *system = Cast<USystemObjective>(obj.Function);
				if (system)
				{
					system->ExecuteBeginplay();
				}
			}
			else
			{
				PrintDebug("Objective Refrence Not Valid", "Core", EDebugtype::CoreSystem);
			}
		}
	}
}

void AQuest::OnConstruction(const FTransform &Transform)
{
	Super::OnConstruction(Transform);
	RefreshQuest();
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuest::StartQuest()
{
	if (IsQuestEnable)
	{
		PrintDebug("Quest Started", "Core", EDebugtype::CoreSystem);
		MachineObjective(Eexutetype::StartObjective, "");
		ReceiveStartQuest();
	}
	else
	{
		PrintDebug("Quest Cant Start becuse is -Disable-", "Core", EDebugtype::CoreSystem);
	}
}

void AQuest::EndQuest()
{
	PrintDebug("Quest Ended  ", "Core", EDebugtype::CoreSystem);
	ReceiveEndQuest();
}

void AQuest::SetEnableQuest(bool Enable)
{
	IsQuestEnable = Enable;
	if (Enable)
	{
		PrintDebug(" -Enable- ", "Core", EDebugtype::CoreSystem);
		if (!FirstStart)
		{
			FirstStart = true;
			for (const auto &obj : Objectives)
			{
				if (obj.Function)
				{
					class USystemObjective *system = Cast<USystemObjective>(obj.Function);
					if (system)
					{
						system->ExecuteBeginplay();
					}
				}
				else
				{
					PrintDebug("Objective Refrence Not Valid", "Core", EDebugtype::CoreSystem);
				}
			}
		}

		ReceiveEnableQuest();
	}
	else
	{
		PrintDebug(" -Disable- ", "Core", EDebugtype::CoreSystem);
		ReceiveDisableQuest();
	}
}

void AQuest::MachineObjective(Eexutetype type, FString Target)
{
	if (IsQuestEnable)
	{
		PrintDebug("<<<<Objective Run>>>", Target, EDebugtype::CoreSystem);
		switch (type)
		{
		case Eexutetype::NextObjective:
			ObjectIndex++;
			RunObjectives(ObjectIndex);
			break;
		case Eexutetype::PreviousObjective:
			ObjectIndex--;
			RunObjectives(ObjectIndex);
			break;
		case Eexutetype::TargetObjective:
			RunObjectiveTarget(Target);
			break;
		case Eexutetype::EndObjective:
			ObjectIndex = Objectives.Num() - 1;
			RunObjectives(ObjectIndex);
			break;
		case Eexutetype::StartObjective:
			ObjectIndex = 0;
			RunObjectives(ObjectIndex);
			break;

		default:
			PrintDebug("Error 189 : I think Close Unreal", "Core", EDebugtype::CoreSystem);
			break;
		}
	}
}

void AQuest::RunObjectiveTarget(FString ObjectiveName)
{
	int debugfor = false;
	for (const auto &obj : Objectives)
	{
		if (obj.Name == ObjectiveName)
		{
			debugfor = true;
			if (obj.Function)
			{
				obj.Function->RunObjective(this, ObjectiveName);
			}
			else
			{
				PrintDebug("Objective Refrence Not Valid", "Core", EDebugtype::CoreSystem);
			}
		}
	}
	if (!debugfor)
	{
		PrintDebug("This Objective is not in Quest Library", ObjectiveName, EDebugtype::CoreSystem);
	}
}

void AQuest::RunObjectiveIndex(int index)
{
	if (Objectives.IsValidIndex(index))
	{
		if (Objectives[index].Function)
		{
			Objectives[index].Function->RunObjective(this, Objectives[index].Name);
		}
		else
		{
			PrintDebug("Objective Refrence Not Valid", "Core", EDebugtype::CoreSystem);
		}
	}
	else
	{
		PrintDebug("This Index Cant find", "Core", EDebugtype::CoreSystem);
	}
}

void AQuest::RunObjectives(int index)
{
	if (index > -1 && index < Objectives.Num())
	{
		if (Objectives[index].Function)
		{
			Objectives[index].Function->RunObjective(this, Objectives[index].Name);
		}
		else
		{
			PrintDebug("Objective Refrence Not Valid", "Core", EDebugtype::CoreSystem);
		}
	}
	else
	{
		EndQuest();
	}
}

void AQuest::PrintDebug(FString Message, FString Objective, EDebugtype type)
{
	FColor messagecolor = FColor::White; // default initialization
	float delay = 10.f;

	switch (type)
	{
	case EDebugtype::Information:
		messagecolor = FColor::White;
		break;
	case EDebugtype::Warning:
		messagecolor = FColor::Yellow;
		break;
	case EDebugtype::Error:
		messagecolor = FColor::Red;
		break;
	case EDebugtype::Update:
		messagecolor = FColor::Blue;
		delay = 0.01f;
		break;
	case EDebugtype::CoreSystem:
		messagecolor = FColor::Black;
		break;
	default: // ensures safety for any unexpected values
		messagecolor = FColor::White;
		break;
	}

	if (EDebugtype::CoreSystem == type)
	{
		if (DebugCoreSystem && IsQuestEnable)
		{
			GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor,FString::Printf(TEXT("[%s :: %s] : %s"), *QuestName, *Objective, *Message));
		}
	}
	else
	{
		if (Debug && IsQuestEnable)
		{
			GEngine->AddOnScreenDebugMessage(-1, delay, messagecolor,FString::Printf(TEXT("[%s :: %s] : %s"), *QuestName, *Objective, *Message));
		}
	}
}

bool AQuest::GetQuestEnable() const
{
	return IsQuestEnable;
}

void AQuest::RefreshQuest()
{
#if WITH_EDITOR
	this->SetActorLabel(QuestName, true);
#endif
}
