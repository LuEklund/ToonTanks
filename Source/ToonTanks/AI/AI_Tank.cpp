// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Tank.h"
#include "Tank_AIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAI_Tank::AAI_Tank()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI_Tank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("AI Controller: %s"), *GetNameSafe(GetController()));

	
}

// Called every frame
void AAI_Tank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Tank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAI_Tank::PossessedBy(AController* NewController)
{
    UE_LOG(LogTemp, Display, TEXT("POSSESEDBY AI Controller"));
    Super::PossessedBy(NewController);

    // Check if the new controller is of the correct type
    if (!NewController || !NewController->IsA(ATank_AIController::StaticClass()))
    {
        // If not, create a new Tank_AIController and assign it
        ATank_AIController* AIController = GetWorld()->SpawnActor<ATank_AIController>(ATank_AIController::StaticClass());
        if (AIController)
        {
            AIController->Possess(this);
        }
    }
}
