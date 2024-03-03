// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraShakeBase.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	caplsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = caplsuleComponent;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(caplsuleComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	porjecttileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Porjectile SpawnPoint"));
	porjecttileSpawnPoint->SetupAttachment(turretMesh);
	

}

void	ABasePawn::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathExplosion, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}



float	ABasePawn::GetHealthPercent() const
{
	return (health->GetHealth() / health->GetMaxHealth());
}



void	ABasePawn::rotateTurret(FVector lookAtTraget)
{
	FVector toTagregt = lookAtTraget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTagregt.Rotation().Yaw, 0.f);

	turretMesh->SetWorldRotation(FMath::RInterpTo(
		turretMesh->GetComponentRotation(),
		lookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		20.f));
}

void	ABasePawn::fire()
{
	/*
	DrawDebugSphere(
		GetWorld(),
		porjecttileSpawnPoint->GetComponentLocation(),
		20.f,
		12,
		FColor::Green,
		false,
		3.f);*/
	AProjectile	*Projectile = GetWorld()->SpawnActor<AProjectile>(
		projectileClass,
		porjecttileSpawnPoint->GetComponentLocation(),
		porjecttileSpawnPoint->GetComponentRotation());
		Projectile->SetOwner(this);
}




