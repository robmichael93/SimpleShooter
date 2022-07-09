// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (AAIController* AIController = OwnerComp.GetAIOwner())
    {
        if (AShooterCharacter* AICharacter = Cast<AShooterCharacter>(AIController->GetPawn()))
        {
            AICharacter->Shoot();
        }
        else
        {
            EBTNodeResult::Failed;
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }

    return EBTNodeResult::Succeeded;   
}