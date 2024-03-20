// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class TOONTANKS_API UItem : public UObject
{
	GENERATED_BODY()

public:
	UItem();
	
	UPROPERTY(Transient)
	class	UWorld* world;

	//How to use item.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FText 				UseActionText;

	//What you see on the ground.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	class UStaticMesh*	PickUpMesh;

	//Viewable image in invetory.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	class UTexture2D*	Thumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FText				ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (Multiline = true))
	FText				ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta = (ClampMin = 0.0f))
	float				Weight;

	//The inventory the item belongs to.
	UPROPERTY()
	class UIventoryComponent*	OwningIventory;

	virtual void Use(class AActor* character);

	UFUNCTION(BlueprintImplementableEvent)
	void	OnUse(class AActor* character);

	virtual class UWorld* GetWorld() const {return world;}
};
