// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IventoryComponent.generated.h"

//Blueprints will bind to this to update the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UIventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:

public:	
	// Sets default values for this component's properties
	UIventoryComponent();

	bool	AddItem(class UItem * Item);
	bool	RemoveItem(class UItem * Item);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UItem*> DefaultItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int32	size;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = "Inventory")
	TArray<class UItem*> Items;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};
