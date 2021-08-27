// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No AI Behaviour tree attached to actor"));
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledPawn = Cast<AShooterCharacter>(GetPawn());
    if (ControlledPawn != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Check"));
        return ControlledPawn->IsDead();
    }

    return true;
}