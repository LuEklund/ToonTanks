// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    camera->SetupAttachment(springArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("fire"), IE_Pressed, this, &ATank::fire);

}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    if (TankPlayerController)
    {
        FHitResult hitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            hitResult);
        
        DrawDebugSphere(
            GetWorld(),
            hitResult.ImpactPoint,
            20,
            12,
            FColor::Red,
            false,
            -1.f);

            rotateTurret(hitResult.ImpactPoint);
    }

}


void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void	ATank::Move(float value)
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());

    FVector deltaLocation(0.f);
    deltaLocation.X = value * dt * speed;

    AddActorLocalOffset(deltaLocation, true);

}


void	ATank::Turn(float value)
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());

    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = value * dt * turnRate;

    AddActorLocalRotation(deltaRotation, true);

}



