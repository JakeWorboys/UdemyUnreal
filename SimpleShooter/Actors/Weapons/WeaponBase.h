// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void virtual PullTrigger();
	void virtual Reload();
	int32 AmmoCount;
	int32 AmmoReserves;
	bool IsReloading;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float BaseDamage = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 MagSize = 1;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo = 1;
	UPROPERTY(EditAnywhere)
	float ReloadLength = 1.0;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
	UParticleSystem* Impact;
	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
	UPROPERTY(EditAnywhere)
	USoundBase* EmptyMag;
	UPROPERTY(EditAnywhere)
	USoundBase* Reloading;

	AController* GetOwnerController();

private:
	void ReloadMechanic();
};
