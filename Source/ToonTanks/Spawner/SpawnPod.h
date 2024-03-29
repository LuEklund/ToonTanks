// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPod.generated.h"

UCLASS()
class TOONTANKS_API ASpawnPod : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPod();

	UPROPERTY(VisibleAnywhere, Category = "Base")
	UStaticMeshComponent	*BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPod")
	float	FallSpeed = 1000.f;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnTower")
	TSubclassOf<AActor>	SpawnEnemy;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
