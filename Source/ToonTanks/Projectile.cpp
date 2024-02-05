// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	projectileMovement->MaxSpeed = maxSpeed;
	projectileMovement->InitialSpeed = speed;
	//projectileMovement->SetupAttachment(projectileMesh);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::onHit);

	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void	AProjectile::onHit(UPrimitiveComponent *hitComponent, AActor *otherActor, UPrimitiveComponent *otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	auto	MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	auto	MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto	DamageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage
		(
			otherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass
		);
		Destroy();
	}
}
