// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "MyFactory.generated.h"

/**
 * 
 */
UCLASS()
class AICOREEDITOR_API UMyFactory : public UFactory
{
    GENERATED_BODY()

public:
    UMyFactory(const FObjectInitializer& ObjectInitializer);

    // Override this function to create an instance of your Data Asset class
    UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};