// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "Components/SkeletalMeshComponent.h"
#include "LauncherProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(Root);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALauncher::PullTrigger() 
{
	Super::PullTrigger();

	if (AmmoCount == 0)
	{
		return;
	}

	AmmoCount--;

	FVector SpawnLocation = ProjectileSpawn->GetComponentLocation();

	AController* OwnerController = GetOwnerController();
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);

	if (ProjectileClass)
	{
		ALauncherProjectile* Projectile = GetWorld()->SpawnActor<ALauncherProjectile>(ProjectileClass, SpawnLocation, OwnerRotation);
		Projectile->SetOwner(this);
	}
}

void ALauncher::Reload() 
{
	Super::Reload();
}

