// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/KismetSystemLibrary.h"

void AEnemyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Display, TEXT("\n============\nNwwwE\n============\n"));

    // Bind movement events
    PlayerInputComponent->BindAxis("MoveForward", this, &AEnemyTank::MoveForward);
}

void AEnemyTank::MoveForward(float Value)
{
    UE_LOG(LogTemp, Display, TEXT("Your message"));
    if (Value != 0.0f)
    {
        FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * Value * MoveSpeed * GetWorld()->GetDeltaSeconds());
        
        SetActorLocation(NewLocation);
        //RootComponent->MoveComponentTo(NewLocation, GetActorRotation(), true);
        
    }
}