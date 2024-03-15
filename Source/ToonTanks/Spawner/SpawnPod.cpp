// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPod.h"
#include "../Tower.h"

// Sets default values
ASpawnPod::ASpawnPod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void ASpawnPod::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPod::Tick(float DeltaTime)
{
	FVector	newPos(this->GetActorLocation());

	Super::Tick(DeltaTime);
	if (this->GetActorLocation().Z <= 81)
	{
		newPos.Z = 85.f;
		Destroy();
		AActor *spawnActor = GetWorld()->SpawnActor<AActor>(SpawnEnemy, newPos, FRotator::ZeroRotator);
	}
	else
	{
		newPos.Z += -450 * DeltaTime;
		this->SetActorLocation(newPos);
	}
}

