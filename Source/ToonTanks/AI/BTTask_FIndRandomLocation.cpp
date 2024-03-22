// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FIndRandomLocation.h"
#include "Tank_AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FIndRandomLocation::UBTTask_FIndRandomLocation(FObjectInitializer const& ObjectInitializer)
    : Super(ObjectInitializer)
{
    NodeName = "Find Random Location In NavMesh";
    UE_LOG(LogTemp, Display, TEXT("Origin1 "));
}

EBTNodeResult::Type UBTTask_FIndRandomLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    //Get AI Controller and its npc
    if (ATank_AIController * const controller = Cast<ATank_AIController>(OwnerComp.GetAIOwner()))
    {
        if (APawn const *npc = controller->GetPawn())
        {
            //Obtain NPC Location to use as an origin
            const FVector Origin = npc->GetActorLocation();

            // Get the navigation system and generate a random Location
            if (auto const * NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
            {
                FNavLocation Loc;
                if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
                }
                //Finish with Success
                FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                return (EBTNodeResult::Succeeded);
            }
        }
    }
    return (EBTNodeResult::Failed);
}
	