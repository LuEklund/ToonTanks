// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealItem.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UHealItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (ClampMin = 0.0f))
	float	HealthToHeal;

protected:
	virtual void Use(AActor* character) override;
	
};
