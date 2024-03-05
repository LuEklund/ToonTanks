// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "MaxHealthPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AMaxHealthPowerUp : public APowerUp
{
	GENERATED_BODY()
public:
	void	ApplyPowerUpEffect(ATank &tank);
};
