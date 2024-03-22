// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "BaseCharacter.h"
#include "ToonTanksPlayerController.h"
#include "ToonTanksSaveGame.h"

void	AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
    if (DeadActor == Tank)
    {
        SaveHighScore();
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledSate(false);
            
            GameOver(false);
        }
    }
    else if (ABaseCharacter * Enemy = Cast<ABaseCharacter>(DeadActor))
    {
        Tank->AddHighScore(Enemy->ScoreOnDeath);
        Enemy->HandleDestruction();
        // --TargetTowers;
        // if (TargetTowers == 0)
        // {
        //     GameOver(true);
        // }
    }

}


void	AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
    
    
}


void	AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTargetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    
    ToonTanksPlayerController->SetPlayerEnabledSate(false);
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
        ToonTanksPlayerController,
        &AToonTanksPlayerController::SetPlayerEnabledSate,
        true);
    GetWorldTimerManager().SetTimer(
        PlayerEnableTimerHandle,
        PlayerEnableTimerDelegate,
        StartDelay,
        false);
}

int32	AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor *>    Towers;
    //UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);

    return (1);
}

void AToonTanksGameMode::SaveHighScore()
{
    GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FPaths::ProjectSavedDir());

    //create instance of save game class
    UToonTanksSaveGame *SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::CreateSaveGameObject(UToonTanksSaveGame::StaticClass()));

    //Get the score
    int32   RoundScore = Tank->GetHighScore();

    //get the saved game instance
    if (UToonTanksSaveGame *PreviousGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::LoadGameFromSlot("Default", 0)))
    {
        //if new highscore save
        if (RoundScore > PreviousGameInstance->Highscore)
        {
            SaveGameInstance->Highscore = Tank->GetHighScore();
            //save the game instance
            UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Default", 0);
        }
    }
}


