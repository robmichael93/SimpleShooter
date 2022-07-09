// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "AIController.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");    
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShooterCharacter* Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    AAIController* AIController = OwnerComp.GetAIOwner();

    if (Player && AIController && AIController->LineOfSightTo(Player))
    {
        // Set Player Location
        AIController->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
    }
    else
    {
        // Clear Player Location
        AIController->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}