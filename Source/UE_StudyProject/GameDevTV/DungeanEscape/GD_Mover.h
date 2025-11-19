// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GD_Mover.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE_STUDYPROJECT_API UGD_Mover : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGD_Mover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	UPROPERTY(EditAnywhere)
	float MoveTime = 4.0f;
	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;
	UPROPERTY(VisibleAnywhere)
	bool ReachedTarget = false;

	FVector StartLocation;
	FVector TargetLocation;
};
