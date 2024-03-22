// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerInShootRange.h"
#include "Tank_AIController.h"
#include "../EnemyTank.h"
#include "../Tank.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerInShootRange::UBTService_PlayerInShootRange(FObjectInitializer const& ObjectInitializer)
{
	bNotifyBecomeRelevant = true;
	TEXT("Player In Range");
}

void UBTService_PlayerInShootRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	// Get the AI Controller
	if (ATank_AIController const *Controller = Cast<ATank_AIController>(OwnerComp.GetAIOwner()))
	{
		//Get the Pawn
		if (AEnemyTank const *AI = Cast<AEnemyTank>(Controller->GetPawn()))
		{
			//Get the character (Player)
			ATank *player = Cast<ATank>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			//set the key to true if player is within range
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), AI->GetDotProductTo(player) <= AI->GetAttackRange());
		}
	}
}
