// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tank_AIController.h"
#include "../EnemyTank.h"

UBTTask_Shoot::UBTTask_Shoot(FObjectInitializer const& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bool OutOfRange = !OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange)
	{
		return (EBTNodeResult::Succeeded);
	}
	else
	{
		//Get Ai Controller
		if (ATank_AIController const *Controller = Cast<ATank_AIController>(OwnerComp.GetOwner()))
		{
			//get AI
			if (AEnemyTank *AI = Cast<AEnemyTank>(Controller->GetPawn()))
			{
				// //If can shoot the shoot
				AI->PreFire();
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return (EBTNodeResult::Succeeded);
			}
		}
	}
	return (EBTNodeResult::Failed);
}
