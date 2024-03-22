// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Tank.h"

void AEnemyTank::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &AEnemyTank::ResetTimerCooldown, fireRate, false);
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AEnemyTank::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) <= Range)
    {
        rotateTurret(Tank->GetActorLocation());
        PreFire();
    }
}

AEnemyTank::AEnemyTank()
{
    SetupStimuluSource();
}

void AEnemyTank::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void AEnemyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyTank::SetupStimuluSource()
{
    StimulusSource  = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
    if (StimulusSource)
    {
        StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
        StimulusSource->RegisterWithPerceptionSystem();
    }
}

void AEnemyTank::PreFire()
{
    if(CanFire)
    {
        CanFire = false;
        GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &AEnemyTank::ResetTimerCooldown, fireRate, false);
        fire();
    }
}

void AEnemyTank::ResetTimerCooldown()
{
    CanFire = true;
}
