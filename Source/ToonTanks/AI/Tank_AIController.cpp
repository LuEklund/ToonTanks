// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank_AIController.h"
#include "../EnemyTank.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ToonTanks/Tank.h"

ATank_AIController::ATank_AIController(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SetupPerceptionSystem();

    // UE_LOG(LogTemp, Display, TEXT("Create AI Controller"));
}


void ATank_AIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    AEnemyTank * const npc = Cast<AEnemyTank>(InPawn);
    
    UBehaviorTree * const tree = npc->GetBehaviorTree();

    UBlackboardComponent *b;
    UseBlackboard(tree->BlackboardAsset, b);
    Blackboard = b;
    RunBehaviorTree(tree);
    

}

void ATank_AIController::SetupPerceptionSystem()
{
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    if (SightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
        SightConfig->SightRadius = 500.f;
        SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
        SightConfig->PeripheralVisionAngleDegrees = 360.f;
        SightConfig->SetMaxAge(5.f);
        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATank_AIController::OnTargetDetected);
        GetPerceptionComponent()->ConfigureSense(*SightConfig);
    }
}

void ATank_AIController::OnTargetDetected(AActor* Actor, const FAIStimulus Stimulus)
{
    if (ATank const *Tank = Cast<ATank>(Actor))
    {
        GetBlackboardComponent()->SetValueAsBool("CanSeePlayer", Stimulus.WasSuccessfullySensed());
    }
}

