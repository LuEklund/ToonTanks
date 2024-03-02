// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void	AToonTanksPlayerController::SetPlayerEnabledSate(bool bPlayerEnable)
{
    if (bPlayerEnable)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bPlayerEnable;
}

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();

	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("ERROR NO HUD"));
	}
}
