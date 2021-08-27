// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "HealthUp.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHealthUp::AHealthUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	BaseMesh->SetupAttachment(RootComponent);

	Pitch = 0.0f;
	Yaw = 0.0f;
	Roll = 0.0f;
}

// Called when the game starts or when spawned
void AHealthUp::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealthUp::OnBoxBeginOverlap);
}

// Called every frame
void AHealthUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator SpinRotation = FRotator(Pitch, Yaw, Roll);
	FQuat Spin = FQuat(SpinRotation);
	AddActorLocalRotation(Spin);
}

void AHealthUp::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Healing, OtherActor->GetOwner()->GetInstigatorController(), this, DamageType);
		Destroy();
	}
}
