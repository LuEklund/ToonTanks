// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Inventory/Item.h"
#include "Inventory/IventoryComponent.h"
#include "BasePawn.h"
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
	inventory =  Cast<ABasePawn>(GetPawn())->inventory;

}

void	AToonTanksPlayerController::UseItem(class UItem* Item)
{
	if (Item)
	{
		Item->Use(Cast<ABasePawn>(GetPawn()));
		Item->OnUse(Cast<ABasePawn>(GetPawn()));
	}
}

UIventoryComponent*	AToonTanksPlayerController::GetInventory()
{
	return(inventory);
	/* if (!GetPawn())
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nNO PAWN\n========================="));
	}
	if (!Cast<ABasePawn>(GetPawn()))
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nBAD CAST\n========================="));
	}
	UE_LOG(LogTemp, Display, TEXT("Your message %s"), *GetPawn()->GetName());
	if (Cast<ABasePawn>(GetPawn())->inventory)
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nGET INV2\n========================="));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nGET NO INV3\n========================="));
	}
	return (Cast<ABasePawn>(GetPawn())->inventory); */
}


