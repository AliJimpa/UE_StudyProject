// Fill out your copyright notice in the Description page of Project Settings.

#include "GameDevTV/DungeanEscape/GD_InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

// Sets default values for this component's properties
UGD_InputComponent::UGD_InputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	// Set up action bindings
}

// Called when the game starts
void UGD_InputComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UWorld *World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Display, TEXT("Can't find World"));
		return;
	}

	APlayerController *PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
	if (!PC)
	{
		UE_LOG(LogTemp, Display, TEXT("Can't find PlayerController"));
		return;
	}

	ULocalPlayer *LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Display, TEXT("Can't find LocalPlayer"));
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		for (UInputMappingContext *CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
	
	if (PC)
	{
		APawn *Pawn = PC->GetPawn();
		// or ACharacter* Char = Cast<ACharacter>(PC->GetPawn());
		UInputComponent *PlayerInputComponent = Pawn->FindComponentByClass<UInputComponent>();
		if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Jumping
			EnhancedInputComponent->BindAction(Interaction, ETriggerEvent::Triggered, this, &UGD_InputComponent::Interact);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}

// Called every frame
void UGD_InputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGD_InputComponent::Interact(const FInputActionValue &Value)
{
	UE_LOG(LogTemp, Display, TEXT("Halllollleeee"));
}
