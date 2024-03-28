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

	UToonTanksSaveGame *SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::CreateSaveGameObject(UToonTanksSaveGame::StaticClass()));
	// Create and Save new game
	if (SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::LoadGameFromSlot("Default", 0)))
	{
		Highscore = SaveGameInstance->Highscore;
		// FString s = FString::Printf(TEXT("loaded game save, %d, %d"), Highscore,  SaveGameInstance->Highscore);
		// GEngine->AddOnScreenDebugMessage(-1, 5-false, FColor::Green,s);
	}
	else
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);
		// GEngine->AddOnScreenDebugMessage(-1, 5-false, FColor::Green, TEXT("Created Game save"));

	}

}
