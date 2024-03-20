// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

#include "Camera/CameraShakeBase.h"


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

	TrailParticels = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticels->SetupAttachment(projectileMesh);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::onHit);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());

	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void	AProjectile::onHit(UPrimitiveComponent *hitComponent, AActor *otherActor, UPrimitiveComponent *otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	AActor	*MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	AController	*MyOwnerInstigator = MyOwner->GetInstigatorController();
	UClass		*DamageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this)
	{
		UGameplayStatics::ApplyDamage
		(
			otherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass
		);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	Destroy();
}
