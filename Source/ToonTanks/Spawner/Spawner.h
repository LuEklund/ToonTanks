// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class TOONTANKS_API ASpawner : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle	SpawnRateTimerHandle;

	void	SpawnSpawnPod();

public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(VisibleAnywhere, Category = "Base")
	UStaticMeshComponent	*BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnPod")
	TSubclassOf<class ASpawnPod> SpawnPodClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnArena")
	FBox	SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnAbleEntities")
	TArray<TSubclassOf<AActor>> SpawnableEntities;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
