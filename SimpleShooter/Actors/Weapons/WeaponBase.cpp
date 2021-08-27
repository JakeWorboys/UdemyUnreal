// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	IsReloading = false;
	AmmoReserves = MaxAmmo;
	AmmoCount = MagSize;
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AWeaponBase::PullTrigger() 
{
	if (IsReloading == true) return;
	if (AmmoCount == 0)
	{
		if (!Cast<APlayerController>(GetOwnerController()))
		{
			Reload();
			return;
		}

		UGameplayStatics::SpawnSoundAttached(EmptyMag, BaseMesh, TEXT("MuzzleFlashSocket"));
		return;
	}

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, BaseMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, BaseMesh, TEXT("MuzzleFlashSocket"));
}

void  AWeaponBase::Reload() 
{
	IsReloading = true;

	UGameplayStatics::SpawnSoundAttached(Reloading, BaseMesh, TEXT("MuzzleFlashSocket"));

	FTimerHandle ReloadDelay;
	GetWorldTimerManager().SetTimer(ReloadDelay, this, &AWeaponBase::ReloadMechanic, ReloadLength, false);
}

void AWeaponBase::ReloadMechanic()
{
	int32 MagToFill = abs(AmmoCount - MagSize);

	if (MagToFill > 0)
	{
		if (AmmoReserves >= MagToFill)
		{
			AmmoCount = MagSize;
			AmmoReserves -= MagToFill;
		}
		else if (AmmoReserves < MagToFill)
		{
			AmmoCount += AmmoReserves;
			AmmoReserves -= AmmoReserves;
		}
	}
	IsReloading = false;
}

AController* AWeaponBase::GetOwnerController() 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}