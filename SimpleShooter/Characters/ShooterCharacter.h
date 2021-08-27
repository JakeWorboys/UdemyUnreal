// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AWeaponBase;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void FireWeapon();
	void ReloadWeapon();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;
	UFUNCTION(BlueprintPure)
	int32 GetAmmoCount() const;
	UFUNCTION(BlueprintPure)
	int32 GetAmmoReserves() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void ToggleSprint();
	void ChangeWeapon();

	UCharacterMovementComponent* MoveComp;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> PrimaryGunClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> SecondaryGunClass;

	UPROPERTY()
	AWeaponBase* PrimaryGun;
	UPROPERTY()
	AWeaponBase* SecondaryGun;
	UPROPERTY()
	AWeaponBase* EquippedGun;

	int32 Sprinting = 0;
	int32 ActiveWeapon = 0;
};
