// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ToonTanksSaveGame.h"

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

    if(APlayerController *PlayerController =  Cast<APlayerController>(Controller))
    {
        if(UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(Inputmapping, 0);
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("UEnhancedInputLocalPlayerSubsystem: FALIED"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("APlayerController: FALIED"));
    }
    if (UEnhancedInputComponent *Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &ATank::MoveForward);
        Input->BindAction(BackwardAction, ETriggerEvent::Triggered, this, &ATank::MoveBackward);
        Input->BindAction(LeftAction, ETriggerEvent::Triggered, this, &ATank::RotateLeft);
        Input->BindAction(RightAction, ETriggerEvent::Triggered, this, &ATank::RotateRight);
        Input->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::PreFire);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("UEnhancedInputComponent: FALIED"));

    }

}

void ATank::AddHighScore(int32  _score)
{
    HighScore += _score;
}

float	ATank::GetFireCooldownPercent() const
{
    float cooldown = this->GetWorldTimerManager().GetTimerRemaining(this->fireRateTimerHandle);
    float clamedCooldown = FMath::Clamp(cooldown / fireRate, 0.f, 1.f);
	return(clamedCooldown);
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
        rotateTurret(hitResult.ImpactPoint);
    }

}


void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATank::ResetTimerCooldown, 0, false);
	TankPlayerController = Cast<APlayerController>(GetController());
}

void	ATank::MoveForward()
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());
    FVector deltaLocation(0.f);
    deltaLocation.X = dt * speed;
    AddActorLocalOffset(deltaLocation, true);
}

void	ATank::MoveBackward()
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());
    FVector deltaLocation(0.f);
    deltaLocation.X = dt * -speed;
    AddActorLocalOffset(deltaLocation, true);
}


void	ATank::RotateLeft()
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());

    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = -dt * turnRate;
    AddActorLocalRotation(FRotator(deltaRotation), true);
}


void	ATank::RotateRight()
{
    float dt = UGameplayStatics::GetWorldDeltaSeconds(this->GetWorld());
    
    FRotator deltaRotation = FRotator::ZeroRotator;
    deltaRotation.Yaw = dt * turnRate;
    AddActorLocalRotation(deltaRotation, true);
}



void	ATank::PreFire()
{
    if (canFire)
    {
        fire();
        canFire = false;
        GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATank::ResetTimerCooldown, fireRate, false);
    }
}


void    ATank::ResetTimerCooldown()
{
    canFire = true;
}

