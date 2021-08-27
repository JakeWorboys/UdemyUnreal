// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorLift.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorLift : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorLift();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	FVector Initial;
	float LastOpened = 0;
	int32 SoundPlayed = 0;

	UPROPERTY()
	UAudioComponent* DoorSound = nullptr;

	UPROPERTY(EditAnywhere)
	float TargetZ = 0;
	UPROPERTY(EditAnywhere)
	float OpenSpeed = 0;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor* TriggerOne = nullptr;
	UPROPERTY(EditAnywhere)
	AActor* TriggerTwo = nullptr;

	void DoorOpening(float DeltaTime);
};
