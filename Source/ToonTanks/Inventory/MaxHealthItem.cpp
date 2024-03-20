// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthItem.h"
#include "IventoryComponent.h"
#include "../BaseCharacter.h"
#include "../HealthComponent.h"


void UMaxHealthItem::Use(AActor* a)
{
    ABaseCharacter *character = Cast<ABaseCharacter>(a);
    if (character)
    {
        character->health->IncreaseMaxHealth(HealthToIncrease);
        if (OwningIventory)
        {
            OwningIventory->RemoveItem(this);
        }
    }
}
