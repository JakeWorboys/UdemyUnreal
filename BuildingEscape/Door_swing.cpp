// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_swing.h"
#include "Components/AudioComponent.h" 
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UDoor_swing::UDoor_swing()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor_swing::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("No trigger assigned to actor"));
	}

	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();

	// UE_LOG(LogTemp, Warning, TEXT("Target yaw is %f"), TargetYaw);
}


// Called every frame
void UDoor_swing::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("Opened = %i"), Opened);

	if (TotalActorWeight() > OpeningMass)
	{
		DoorOpening(DeltaTime);
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() >= (LastOpened + 1))
		{
			DoorClosing(DeltaTime);
		}
	}
}

void UDoor_swing::DoorOpening(float DeltaTime)
{
	FRotator DoorOpen{0, FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime, OpenSpeed), 0};
	GetOwner()->SetActorRotation(DoorOpen);
	LastOpened = GetWorld()->GetTimeSeconds();
	if (SoundPlayed == 0)
	{
		SoundPlayed = 1;
		DoorSound->Play();
	}
}

void UDoor_swing::DoorClosing(float DeltaTime)
{
	FRotator DoorOpen{0, FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, InitialYaw, DeltaTime, 2), 0};
	GetOwner()->SetActorRotation(DoorOpen);
	if (SoundPlayed == 1)
	{
		SoundPlayed = 0;
		DoorSound->Play();
	}
}

float UDoor_swing::TotalActorWeight()
{
	float TotalMass = 0.f;

	TArray<AActor*> TriggeringActors;
	PressurePlate->GetOverlappingActors(OUT TriggeringActors);

	for (AActor* Actor : TriggeringActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}