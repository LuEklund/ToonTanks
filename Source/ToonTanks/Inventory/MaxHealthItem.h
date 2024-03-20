// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "MaxHealthItem.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UMaxHealthItem : public UItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (ClampMin = 0.0f))
	float	HealthToIncrease;

protected:
	virtual void Use(AActor* character) override;
	
};
