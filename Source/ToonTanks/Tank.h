// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void	HandleDestruction();

	APlayerController *GetPlayerController() const {return (TankPlayerController);}

	bool	bAlive = true;

	UFUNCTION(BlueprintPure, Category = "Combat")
	float	GetFireCooldownPercent() const;

	void	IncreaseSpeed(float speed);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float	speed = 500.f;	

	UPROPERTY(EditAnywhere, Category = "Movement")
	float	turnRate = 50.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FTimerHandle	fireRateTimerHandle;
	float			fireRate = .5f;
	bool			canFire = true;


	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	class USpringArmComponent *springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	class UCameraComponent *camera;

	APlayerController *TankPlayerController;

	void			Move(float value);
	void			Turn(float value);

	void			PreFire();
	void			ResetTimerCooldown();
	
};
