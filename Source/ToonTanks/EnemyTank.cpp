// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

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
	UE_LOG(LogTemp, Display, TEXT("\n============\n%s\n============\n"), *this->GetName());

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

void AEnemyTank::SetupStimuluSource()
{
    StimulusSource  = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
    if (StimulusSource)
    {
        StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
        StimulusSource->RegisterWithPerceptionSystem();
    }
}
