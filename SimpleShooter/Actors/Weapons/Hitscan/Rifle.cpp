// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARifle::ARifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARifle::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARifle::PullTrigger()
{
	Super::PullTrigger();

	if (AmmoCount == 0)
	{
		return;
	}

	AmmoCount--;
	
	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location, ShotDirection.Rotation());
		
		if (Hit.GetActor() != nullptr)
		{
			FPointDamageEvent DamageEvent(BaseDamage, Hit, ShotDirection, nullptr);
			Hit.GetActor()->TakeDamage(BaseDamage, DamageEvent, GetOwnerController(), this);
			// FString HitActor = Hit.GetActor()->GetName();
			// UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor);
		} 
	}
}

bool ARifle::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{
	AController* OwnerController = GetOwnerController();
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);
	ShotDirection = -OwnerRotation.Vector();

	FVector End = OwnerLocation + OwnerRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, OwnerLocation, End, ECC_GameTraceChannel1, Params);
}

void ARifle::Reload() 
{
	Super::Reload();
}