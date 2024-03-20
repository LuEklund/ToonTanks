// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseCharacter.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AEnemyTank : public ABaseCharacter
{
	GENERATED_BODY()

public:
	UBehaviorTree *GetBehaviorTree() const {return (this->Tree);}

	AEnemyTank();

	void	HandleDestruction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="yes"))
	float MoveSpeed = 100.f;

protected:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	void MoveForward(float Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="yes"))
	UBehaviorTree *Tree;

private:
	class UAIPerceptionStimuliSourceComponent *StimulusSource;

	void	SetupStimuluSource();
};
