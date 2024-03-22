// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TOONTANKS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	virtual void	HandleDestruction();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float	GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void	UseItem(class UItem* Item);

protected:
	void	fire();
	void	rotateTurret(FVector lookAtTraget);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent *baseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	UStaticMeshComponent *turretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "True"))
	USceneComponent *porjecttileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> projectileClass;

	UPROPERTY(EditAnywhere, Category = "Death")
	UParticleSystem *DeathExplosion;

	UPROPERTY(EditAnywhere, Category = "Death")
	class	USoundBase *DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	UPROPERTY(EditAnywhere, Category="MOvement")
	class UMovementComponent	*MovementComponent;


	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	class UIventoryComponent *inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UHealthComponent *health;

	FTimerHandle	fireRateTimerHandle;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float			fireRate = .51f;

	int32			ScoreOnDeath = 1;

};
