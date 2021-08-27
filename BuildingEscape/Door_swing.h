// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "Door_swing.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoor_swing : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor_swing();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void DoorOpening(float DeltaTime);
	void DoorClosing(float DeltaTime);
	float TotalActorWeight();

private:
	int32 SoundPlayed = 0;
	float InitialYaw;
	float LastOpened = 0;

	UPROPERTY()
	UAudioComponent* DoorSound = nullptr;

	UPROPERTY(EditAnywhere)
	float TargetYaw = 0;
	UPROPERTY(EditAnywhere)
	int32 CloseDelay = 0;
	UPROPERTY(EditAnywhere)
	float OpeningMass = 50.f;
	UPROPERTY(EditAnywhere)
	float OpenSpeed = 0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
};
