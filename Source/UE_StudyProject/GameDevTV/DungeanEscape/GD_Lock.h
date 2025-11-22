// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// #include "Componenets/SceneComponent.h"
// #include "Componenets/StaticMeshComponent.h"
#include "GD_BoxTrigger.h"
#include "GD_Lock.generated.h"

UCLASS()
class UE_STUDYPROJECT_API AGD_Lock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGD_Lock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent *root;
	UPROPERTY(EditAnywhere)
	UGD_BoxTrigger *myTrigger;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent *mesh;
	UPROPERTY(EditAnywhere)
	FString KeyItemName;

	void SetIsKeyPlaced(bool enable);
	bool GetIsKeyPlaced();
	UPROPERTY(EditAnywhere)
	bool isKeyPlaced = false;
};
