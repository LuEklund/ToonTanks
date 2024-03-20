// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "Inventory/Item.h"
#include "Inventory/IventoryComponent.h"
#include "BaseCharacter.h"
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
	UE_LOG(LogTemp, Display, TEXT("This: %p, GetPawn %p, GetCharacter %p"), this, GetPawn(), GetCharacter());

	inventory =  Cast<ABaseCharacter>(GetCharacter())->inventory;

}

void	AToonTanksPlayerController::UseItem(class UItem* Item)
{

	if (Item)
	{
		Item->Use(Cast<ABaseCharacter>(GetCharacter()));
		Item->OnUse(Cast<ABaseCharacter>(GetCharacter()));
	}
}

UIventoryComponent*	AToonTanksPlayerController::GetInventory()
{
	return(inventory);
	/* if (!GetPawn())
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nNO PAWN\n========================="));
	}
	if (!Cast<ABaseCharacter>(GetPawn()))
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nBAD CAST\n========================="));
	}
	UE_LOG(LogTemp, Display, TEXT("Your message %s"), *GetPawn()->GetName());
	if (Cast<ABaseCharacter>(GetPawn())->inventory)
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nGET INV2\n========================="));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("\n=====================\nGET NO INV3\n========================="));
	}
	return (Cast<ABaseCharacter>(GetPawn())->inventory); */
}


