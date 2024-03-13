// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthItem.h"
#include "IventoryComponent.h"
#include "../BasePawn.h"


void UMaxHealthItem::Use(class ABasePawn* character)
{
    if (character)
    {
        character->health->IncreaseMaxHealth(HealthToIncrease);
        if (OwningIventory)
        {
            OwningIventory->RemoveItem(this);
        }
    }
}
