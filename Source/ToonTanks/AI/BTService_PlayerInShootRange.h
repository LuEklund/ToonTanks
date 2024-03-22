// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerInShootRange.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UBTService_PlayerInShootRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_PlayerInShootRange(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};


