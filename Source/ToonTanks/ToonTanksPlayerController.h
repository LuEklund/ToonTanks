// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UUserWidget *HUD;

	class UIventoryComponent *inventory;

protected:
	virtual void BeginPlay() override;

public:
	void	SetPlayerEnabledSate(bool bPlayerEnable);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void	UseItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Items")
	class UIventoryComponent*	GetInventory();
	
};
