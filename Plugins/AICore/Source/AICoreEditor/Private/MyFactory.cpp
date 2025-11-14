// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFactory.h"

UMyFactory::UMyFactory(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    bCreateNew = true;
    bEditAfterNew = true;
    //SupportedClass = UAIBehavior::StaticClass(); // Set to your Data Asset class
}

UObject *UMyFactory::FactoryCreateNew(UClass *Class, UObject *InParent, FName Name, EObjectFlags Flags, UObject *Context, FFeedbackContext *Warn)
{
    // Create an instance of your Data Asset class
    //UAIBehavior *NewDataAsset = NewObject<UAIBehavior>(InParent, Class, Name, Flags | RF_Transactional);

    // Customize the Data Asset here if needed

    return nullptr;
}