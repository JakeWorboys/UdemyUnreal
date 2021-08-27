// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimer, this, &APawnTurret::CheckFireCondition, FireRate, true);
    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (!PlayerPawn || ReturnDistanceToPlayer() > TurretRange)
    {
        return;
    }
    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
    {
        return;
    }
    if (ReturnDistanceToPlayer() <= TurretRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if (!PlayerPawn)
    {
        return 0;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}