// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StudyActor.generated.h"

UCLASS()
class UE_STUDYPROJECT_API AStudyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStudyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveActor(float deltatime);
	void RotateActor(float deltatime);
	float GetDistanceMoved(FVector CurrentLoc);
	FVector startLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector actorVelocity = FVector(1,0,0);
	UPROPERTY(EditAnywhere)
	FRotator rotateVelocity = FRotator(1,0,0);
	UPROPERTY(EditAnywhere)
	float moveDistance = 10;

};
