// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "AIController.h"


UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Shoot Target");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* ControlledPawn = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    
    if (ControlledPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    ControlledPawn->FireWeapon();
    return EBTNodeResult::Succeeded;
}

