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

    //create instance of save game class
    UToonTanksSaveGame *SaveGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::CreateSaveGameObject(UToonTanksSaveGame::StaticClass()));
    if (Tank->GetHighScore() > SaveGameInstance->Highscore)
    {
        SaveGameInstance->Highscore = Tank->GetHighScore();
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Default"), 0);
    }
    // FString s = FString::Printf(TEXT("GAME SAVED %d, %d"), SaveGameInstance->Highscore, Tank->GetHighScore());
    // GEngine->AddOnScreenDebugMessage(-1, 5-false, FColor::Green, s);
    //get the saved game instance
    // if (UToonTanksSaveGame *PreviousGameInstance = Cast<UToonTanksSaveGame>(UGameplayStatics::LoadGameFromSlot("Default", 0)))
    // {
    //     //if new highscore save
    //     if (Tank->GetHighScore() > PreviousGameInstance->Highscore)
    //     {
    //         FAsyncSaveGameToSlotDelegate SavedDelegate;
    //         //save the game instance
    //         UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Default", 0, SavedDelegate);
    //         //UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Default", 0);
    //     }
    // }
}


