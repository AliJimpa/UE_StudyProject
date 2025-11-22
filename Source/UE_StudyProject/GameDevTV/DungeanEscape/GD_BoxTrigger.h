// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GD_Mover.h"
#include "GD_BoxTrigger.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE_STUDYPROJECT_API UGD_BoxTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	UGD_BoxTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** called when something enters the sphere component */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp, 
		class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	/** called when something leaves the sphere component */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp, 
		class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	AActor *TargetDoor;
	UPROPERTY(EditAnywhere)
	FName BeginTag;
	UPROPERTY(EditAnywhere)
	FName EndTag;
	UPROPERTY(VisibleAnywhere)
	bool isTrigger = false;
	UPROPERTY(VisibleAnywhere)
	int OberlapCount = 0;


	UGD_Mover *DoorMover;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void SetTigger(bool enable);
};
