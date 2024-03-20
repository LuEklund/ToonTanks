// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABaseCharacter
{
	GENERATED_BODY()

	
public:
	virtual void Tick(float DeltaTime) override;
	void	HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	class ATank *tank;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float fireRange = 700.f;

	FTimerHandle	fireRateTimerHandle;
	float			fireRate = 2.f;
	void			checkFireCondition();

	bool			inFireRange();
	
};
