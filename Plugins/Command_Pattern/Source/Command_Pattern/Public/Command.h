// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Command.generated.h"


UENUM(Blueprintable,BlueprintType)
enum EDebugtypeC
{
	Information,
	Warning,
	Error,
	Update,
	CoreSystem,
};
/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class COMMAND_PATTERN_API UCommand : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Execute(class AActor* Owner , class AActor* Parent ,class UPrimitiveComponent *OverlappedComp ,const FHitResult &SweepResult);	

	void NativeExecute();

	bool ShowDebug = false;


protected:

	UFUNCTION(BlueprintCallable)
		void Debug(class ACommandTrigger* Owner ,FString Message, EDebugtypeC type);
	UFUNCTION(BlueprintCallable)
		void FinishCommand();


private:

	float timer = 0;

	UFUNCTION(BlueprintCallable)
		bool Timer(float deltatime ,float Duration);

	UFUNCTION(BlueprintCallable,meta = (AllowPrivateAccess = "true"))
		float GetTimer() const;
	UFUNCTION(BlueprintCallable,meta = (AllowPrivateAccess = "true"))
		void ResetTimer();

	
	
};
