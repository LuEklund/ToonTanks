// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_AIController.h"
#include "AI_Tank.h"

ATank_AIController::ATank_AIController(FObjectInitializer const& ObjectInitializer)
{
    UE_LOG(LogTemp, Display, TEXT("Create AI Controller"));
}


void ATank_AIController::OnPossess(APawn *InPawn)
{
    UE_LOG(LogTemp, Display, TEXT("POSSESED AI Controller"));
    Super::OnPossess(InPawn);
    AAI_Tank * const npc = Cast<AAI_Tank>(InPawn);
    
    UBehaviorTree * const tree = npc->GetBehaviorTree();

    UBlackboardComponent *b;
    UseBlackboard(tree->BlackboardAsset, b);
    Blackboard = b;
    RunBehaviorTree(tree);
    

}

