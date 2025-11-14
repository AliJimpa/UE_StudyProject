// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AILocator.generated.h"

UCLASS()
class SIMPLEAISYSTEM_API AAILocator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAILocator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable, Category = "AISystem|AILocator")
	void SetActorTitle(FString name);

};
