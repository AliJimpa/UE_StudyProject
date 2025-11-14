// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACController.generated.h"

class UACCoreTask;


UCLASS( abstract , BlueprintType , ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AICORERUNTIME_API UACController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , meta = (AllowPrivateAccess = "true") , Category = "AICore|Controller");
	TSubclassOf<UACCoreTask> MasterTask;

	UACCoreTask* CoreTask;

		
};
