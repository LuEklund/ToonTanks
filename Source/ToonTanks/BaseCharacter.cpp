// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

#include "Inventory/Item.h"
#include "Projectile.h"

#include "HealthComponent.h"
#include "Inventory/IventoryComponent.h"
#include "GameFramework/MovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("Movement"));

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	porjecttileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Porjectile SpawnPoint"));
	porjecttileSpawnPoint->SetupAttachment(turretMesh);

	inventory = CreateDefaultSubobject<UIventoryComponent>(TEXT("Inventory"));
	

}

void ABaseCharacter::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathExplosion, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseCharacter::GetHealthPercent() const
{
	return (health->GetHealth() / health->GetMaxHealth());
}

void ABaseCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this);
	}
}

void ABaseCharacter::rotateTurret(FVector lookAtTraget)
{
	FVector toTagregt = lookAtTraget - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTagregt.Rotation().Yaw, 0.f);

	turretMesh->SetWorldRotation(FMath::RInterpTo(
	turretMesh->GetComponentRotation(),
	lookAtRotation,
	UGameplayStatics::GetWorldDeltaSeconds(this),
	20.f));
}

void ABaseCharacter::fire()
{
	AProjectile	*Projectile = GetWorld()->SpawnActor<AProjectile>(
	projectileClass,
	porjecttileSpawnPoint->GetComponentLocation(),
	porjecttileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}

