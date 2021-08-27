// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "Engine/World.h" 
#include "GameFramework/PlayerController.h" 
#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h" 

// Make OUT parameters stand out for readability
#define OUT

UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	GetPhysicsHandle();
	InputSetup();
}

// Checks for physics handle on actor and saves it to class variable
void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle component attached to object %s"), *GetOwner()->GetName());
	}
}

// Assigns inputs to player character for grabber component
void UGrabber::InputSetup()
{
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
		
	InputComp->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
	InputComp->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	// UE_LOG(LogTemp, Warning, TEXT("Grabbed"));
	FHitResult HitResult = GetFirstActorHit();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd()
		);
	}
}

void UGrabber::Release()
{
	// UE_LOG(LogTemp, Warning, TEXT("Released"));
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugLine(
	GetWorld(),
	PlayerLocation,
	LineTraceEnd(),
	FColor(255, 0, 0),
	false,
	0.f,
	0,
	5
);

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd());
	}
}

// Raycast on call, return first actor within rays
FHitResult UGrabber::GetFirstActorHit()
{
	FVector GrabLength = LineTraceEnd();
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerLocation,
		GrabLength,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("\n%s"), *Hit.GetActor()->GetName());
	}
	return Hit;
}

// Calculate player view vector for range of grab component
FVector UGrabber::LineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);
	FVector LineDirection = PlayerRotation.Vector() * Reach;



	return PlayerLocation + LineDirection;
}