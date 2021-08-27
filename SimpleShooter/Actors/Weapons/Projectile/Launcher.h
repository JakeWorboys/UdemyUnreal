// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleShooter/Actors/Weapons/WeaponBase.h"
#include "Launcher.generated.h"

class ALauncherProjectile;

UCLASS()
class SIMPLESHOOTER_API ALauncher : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauncher();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void virtual PullTrigger() override;
	void virtual Reload() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ProjectileSpawn;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ALauncherProjectile> ProjectileClass;
};
