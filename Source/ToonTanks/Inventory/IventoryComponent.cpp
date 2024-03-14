// Fill out your copyright notice in the Description page of Project Settings.


#include "IventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UIventoryComponent::UIventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	size = 20;

}


// Called when the game starts
void UIventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	for (UItem* item : DefaultItems)
	{
		AddItem(item);
	}
}


bool	UIventoryComponent::AddItem(class UItem * _item)
{
	if (Items.Num() >= size || !_item)
	{
		return (false);
	}
	_item->OwningIventory = this;
	_item->world = GetWorld();
	Items.Add(_item);

	//Update UI
	OnInventoryUpdated.Broadcast();
	return (true);
}	

bool	UIventoryComponent::RemoveItem(class UItem * _item)
{
	if (_item)
	{
		_item->OwningIventory = nullptr;
		_item->world = nullptr;
		Items.RemoveSingle(_item);

		//Update UI
		OnInventoryUpdated.Broadcast();
		return (true);
	}
	return (false);
}