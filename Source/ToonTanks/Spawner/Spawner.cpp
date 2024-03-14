// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "SpawnPod.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	int	num = FMath::RandRange(0, SpawnableEntities.Num());
	UE_LOG(LogTemp, Display, TEXT("Array Size %i, num %i"), SpawnableEntities.Num(), num);
	if (num >= 0)
	{
		FVector pos(this->GetActorLocation());
		pos.Z -= 50.f;

		ASpawnPod *spawnActor = GetWorld()->SpawnActor<ASpawnPod>(SpawnPodClass, pos, FRotator::ZeroRotator);
		//AActor* spawnActor = GetWorld()->SpawnActor<ASpawnPod>(ASpawnPod::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
	}
	
}



