// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

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
    UE_LOG(LogTemp, Display, TEXT("Your message"));
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	playerControllerRef = Cast<APlayerController>(GetController());
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



