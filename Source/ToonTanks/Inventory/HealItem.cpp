// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItem.h"
#include "IventoryComponent.h"
#include "../BaseCharacter.h"
#include "../HealthComponent.h"


void UHealItem::Use(AActor* a)
{
    ABaseCharacter *character = Cast<ABaseCharacter>(a);
    if (character)
    {
        character->health->SetHealth(character->health->GetHealth() + HealthToHeal);

        if (OwningIventory)
        {
            OwningIventory->RemoveItem(this);
        }

    }
}

