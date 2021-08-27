// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthUp.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API AHealthUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthUp();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Healing", meta = (AllowPrivateAccess = "true"))
	float Healing = -20.0f;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Pitch;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Yaw;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Roll;

	UPROPERTY(EditDefaultsOnly, Category = "Healing")
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
