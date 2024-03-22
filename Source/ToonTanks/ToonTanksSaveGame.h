// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ToonTanksSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UToonTanksSaveGame : public USaveGame
{
	GENERATED_BODY()

	
public:
	UToonTanksSaveGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	Highscore = 0;
};
