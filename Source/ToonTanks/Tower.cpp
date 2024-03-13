// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (inFireRange())
    {
        rotateTurret(tank->GetActorLocation());
    }
}

void	ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


void ATower::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    UE_LOG(LogTemp, Display, TEXT("\n=====================\nCREATING TOWER\n========================="));

    GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::checkFireCondition, fireRate, true);
}


void ATower::checkFireCondition()
{
    if (tank == nullptr)
    {
        return;
    }
    if (inFireRange() && tank->bAlive)
    {
        fire();
    }
}

bool ATower::inFireRange()
{
    if (tank)
    {
        FVector tankLocation = tank->GetActorLocation();
        float disantce = FVector::Dist(GetActorLocation(), tankLocation);
        if (disantce <= fireRange)
        {
            return (true);
        }
    }
    return (false);
}
