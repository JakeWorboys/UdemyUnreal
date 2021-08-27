// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorLift.h"
#include "Components/AudioComponent.h" 
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UDoorLift::UDoorLift()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorLift::BeginPlay()
{
	Super::BeginPlay();

	Initial = GetOwner()->GetActorLocation();
	TargetZ += Initial.Z;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("No trigger assigned to actor"));
	}

	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();

	// UE_LOG(LogTemp, Warning, TEXT("Target yaw is %f"), TargetYaw);
}


// Called every frame
void UDoorLift::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// UE_LOG(LogTemp, Warning, TEXT("Opened = %i"), Opened);

	if (PressurePlate->IsOverlappingActor(TriggerOne) && PressurePlate->IsOverlappingActor(TriggerTwo))
	{
		DoorOpening(DeltaTime);
	}
}

void UDoorLift::DoorOpening(float DeltaTime)
{
	FVector DoorOpen{Initial.X, Initial.Y, FMath::FInterpTo(GetOwner()->GetActorLocation().Z, TargetZ, DeltaTime, OpenSpeed)};
	GetOwner()->SetActorLocation(DoorOpen);
	LastOpened = GetWorld()->GetTimeSeconds();
	if (SoundPlayed == 0)
	{
		SoundPlayed = 1;
		DoorSound->Play();
	}
}