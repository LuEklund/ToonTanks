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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	UBehaviorTree *GetBehaviorTree() const {return (this->Tree);}

	AEnemyTank();

	void	HandleDestruction();
	
	bool	GetCanFire() { return (CanFire);}

	float	GetAttackRange() const { return (Range);}
	
	void			PreFire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="yes"))
	float MoveSpeed = 100.f;

protected:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(AllowPrivateAccess="yes"))
	UBehaviorTree *Tree;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="combat", meta=(AllowPrivateAccess="true"))
	float Range = 200.f;
	
	class UAIPerceptionStimuliSourceComponent *StimulusSource;

	void	SetupStimuluSource();

	bool			CanFire = false;
	void			ResetTimerCooldown();

	class ATank		*Tank;


};
