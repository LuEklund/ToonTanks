// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "SpawnPod.h"
#include "Kismet/KismetMathLibrary.h"

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
	GetWorldTimerManager().SetTimer(SpawnRateTimerHandle, this, &ASpawner::SpawnSpawnPod, SpawnTimer, true);
}

void	ASpawner::SpawnSpawnPod()
{

	if (ShouldSpawn == false || SpawnableEntities.Num() < 1)
	{
		return ;
	}
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox_Box(SpawnArea);

	int	num = FMath::RandRange(0, SpawnableEntities.Num() - 1);
	FVector pos(this->GetActorLocation());
	pos.Z -= 50.f;

	ASpawnPod *SpawnPod = GetWorld()->SpawnActor<ASpawnPod>(SpawnPodClass, RandomPoint, FRotator::ZeroRotator);
	SpawnPod->SpawnEnemy = SpawnableEntities[num];

>>>>>>> 0697f8664843a586889cbd27a9930eccc176803c
}



