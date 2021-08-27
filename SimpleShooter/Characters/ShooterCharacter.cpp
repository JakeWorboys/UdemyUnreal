// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "SimpleShooter/Actors/Weapons/WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooter/Gamemodes/SimpleShooterModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveComp = Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	PrimaryGun = GetWorld()->SpawnActor<AWeaponBase>(PrimaryGunClass);
	SecondaryGun = GetWorld()->SpawnActor<AWeaponBase>(SecondaryGunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	PrimaryGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	SecondaryGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	PrimaryGun->SetOwner(this);
	SecondaryGun->SetOwner(this);

	EquippedGun = PrimaryGun;
	SecondaryGun->SetHidden(true);
	ActiveWeapon = 0;

	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Action mapping
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ToggleSprint"), IE_Pressed, this, &AShooterCharacter::ToggleSprint);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::FireWeapon);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AShooterCharacter::ReloadWeapon);
	PlayerInputComponent->BindAction(TEXT("NextWeapon"), IE_Pressed, this, &AShooterCharacter::ChangeWeapon);

	//Axis mapping
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageApplied, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), CurrentHealth);

	if (IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ASimpleShooterModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
	}

	return DamageApplied;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::ToggleSprint()
{
	if (Sprinting == 0)
	{
		Sprinting = 1;
		MoveComp->MaxWalkSpeed = 1200;
	}
	else
	{
		Sprinting = 0;
		MoveComp->MaxWalkSpeed = 600;
	}
}

void AShooterCharacter::ChangeWeapon() 
{
	if (ActiveWeapon == 0)
	{
		PrimaryGun->SetActorHiddenInGame(true);
		SecondaryGun->SetActorHiddenInGame(false);
		EquippedGun = SecondaryGun;
		ActiveWeapon = 1;
	}
	else if (ActiveWeapon == 1)
	{
		SecondaryGun->SetActorHiddenInGame(true);
		PrimaryGun->SetActorHiddenInGame(false);
		EquippedGun = PrimaryGun;
		ActiveWeapon = 0;
	}
}

void AShooterCharacter::FireWeapon()
{
	EquippedGun->PullTrigger();
}

void AShooterCharacter::ReloadWeapon() 
{
	EquippedGun->Reload();
}

bool AShooterCharacter::IsDead() const
{
	if (CurrentHealth != 0)
	{
		return false;
	}
	return true;
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

int32 AShooterCharacter::GetAmmoCount() const
{
	return EquippedGun->AmmoCount;
}

int32 AShooterCharacter::GetAmmoReserves() const
{
	return EquippedGun->AmmoReserves;
}
