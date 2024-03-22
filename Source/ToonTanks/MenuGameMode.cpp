// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"

#include "ToonTanksSaveGame.h"
#include "Kismet/GameplayStatics.h"

AMenuGameMode::AMenuGameMode()
{
	
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	//load saved game
	UToonTanksSaveGame *SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::LoadGameFromSlot("Default", 0));
	if (SaveGameInstance)
	{
		//Get current Highscore
		Highscore = SaveGameInstance->Highscore;
	}
	else
	{
		// Create and Save new game
		SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::CreateSaveGameObject(UToonTanksSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Default", 0);
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FPaths::ProjectSavedDir());
	}

}
