// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABaseCharacter
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

	void	AddHighScore(int32 _score);
	int32	GetHighScore() const {return (HighScore);}

	UFUNCTION(BlueprintPure, Category = "Combat")
	float	GetFireCooldownPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext	*Inputmapping;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction	*ForwardAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction	*BackwardAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction	*LeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction	*RightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction	*FireAction;
	
private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float	speed = 500.f;	

	UPROPERTY(EditAnywhere, Category = "Movement")
	float	turnRate = 50.f;

	int32			HighScore = 0;
	bool			canFire = true;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	class USpringArmComponent *springArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	class UCameraComponent *camera;

	APlayerController *TankPlayerController;

	void			MoveForward();
	void			MoveBackward();
	void			RotateLeft();
	void			RotateRight();

	void			PreFire();
	void			ResetTimerCooldown();
	
};
