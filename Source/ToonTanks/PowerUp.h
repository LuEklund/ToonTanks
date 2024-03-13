// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"
class ATank;

UCLASS()
class TOONTANKS_API APowerUp : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base", meta = (AllowPrivateAccess = "True"))
	class	UStaticMeshComponent *baseMesh;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Sets default values for this actor's properties
	APowerUp();
	virtual void	ApplyPowerUpEffect(ATank &tank);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	class	UItem	*item;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
