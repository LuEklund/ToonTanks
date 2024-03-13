// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Tank.h"
#include "Inventory/Item.h"
#include "Inventory/IventoryComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = baseMesh;

	item = CreateDefaultSubobject<UItem>(TEXT("Pickup Item"));


}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
	//baseMesh->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	baseMesh->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlap);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	baseMesh->AddLocalRotation(FRotator(0, -45.f * DeltaTime, 0));
}


void APowerUp::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATank *TankActor = Cast<ATank>(OtherActor);
	if (TankActor)
	{
		TankActor->inventory->AddItem(item);
		//ApplyPowerUpEffect(*TankActor);
    	Destroy();
	}
}

void APowerUp::ApplyPowerUpEffect(ATank &_tank)
{
	UE_LOG(LogTemp, Display, TEXT("NO EFFECT"));
}