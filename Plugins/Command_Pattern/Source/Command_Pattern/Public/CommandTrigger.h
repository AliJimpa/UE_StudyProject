// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command.h"
#include "Engine/TriggerBox.h"
#include "CommandTrigger.generated.h"


USTRUCT(Blueprintable)
struct FCommandReal
{
	GENERATED_BODY()

	/** Sprite category that the component belongs to */
	UPROPERTY(EditAnywhere)
		UCommand* Command ;

	/** Localized name of the sprite category */
	UPROPERTY(EditAnywhere)
	float Timeline;
};


UENUM(Blueprintable,BlueprintType)
enum ExcuteType
{
	BeginOverlap,
	EndOverlap,
	Interact,
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FCommandRun , UCommand* , Command , ExcuteType , Type);
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FTick , float , Deltatime );


UCLASS()
class COMMAND_PATTERN_API ACommandTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:	

	ACommandTrigger(); 

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void DelayTime(FName Methodname, float Time);

	
	
	UFUNCTION()
	virtual	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



	// BeginOverlap Trigger parameter
	bool BeginGate = false;
	class AActor *BeginActor;
    class UPrimitiveComponent *BeginComp;
    FHitResult BeginHit;
	int BeginIndex = 0;
	bool BeginRunTime = false;
	float BeginTimer = 0;

	// EndOverlap Trigger parameter
	bool EndGate = false;
	class AActor *EndActor;
    class UPrimitiveComponent *EndComp;
    FHitResult EndHit;
	int EndIndex = 0;
	bool EndRunTime = false;
	float EndTimer = 0;

	
private:
	void BeginReset();
	void EndReset();

	UFUNCTION()
		void BeginExcuteCommand();
	UFUNCTION()
		void EndExcuteCommand();





	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		void FPlaySound2D(  USoundBase* Sound, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, USoundConcurrency* ConcurrencySettings = nullptr, const AActor* OwningActor = nullptr, bool bIsUISound = true);
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		void FPlaySoundAtLocation( USoundBase* Sound, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, USoundConcurrency* ConcurrencySettings = nullptr, UInitialActiveSoundParams* InitialParams = nullptr);
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		AActor* FSpawnActor(UClass* ChildActorClass , FName ChildActorName, FVector const Location , FRotator const Rotation);
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		APlayerController* FGetPlayerController(int index) const;
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		ACharacter* FGetPlayerCharacter(int index) const;
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (AllowPrivateAccess = "true"))
		UUserWidget* FCreateWidget(TSubclassOf<UUserWidget> WidgetClass); 





public:

	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" , meta = (DisplayName = "Debug"))
	void PrintDebug(FString Message, FString Objective, EDebugtypeC type);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Trigger")
		FName PlayerTag;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Trigger")
		TArray<FCommandReal> BeginOverlap = TArray<FCommandReal>();
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Trigger")
		TArray<FCommandReal> EndOverlap = TArray<FCommandReal>();
	UPROPERTY(EditAnywhere,AdvancedDisplay,Category = "Trigger")
		bool Debug = false;
	UPROPERTY(EditAnywhere,AdvancedDisplay,Category = "Trigger")
		bool DebugCoreSystem = false;


	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FCommandRun CommandRun;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
		FTick TickUpdate;




private:

	TArray<AActor*> ActorBank  = TArray<AActor*>();
	TArray<UUserWidget*> WidgetBank = TArray<UUserWidget*>();;

	
	

protected: 

	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" )
		bool DestroyActorID(int ID);
	UFUNCTION(BlueprintCallable, Category = "CoreGame|CommandTrigger|Functions" )
		bool DestroyWidgetID(int ID);

	AActor* GetActorID(int ID);
	UUserWidget* GetWidgetID(int ID);
	bool IsPlayerTag(AActor* Target) const;






};
