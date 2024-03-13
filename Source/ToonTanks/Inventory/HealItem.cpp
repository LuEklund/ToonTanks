// Fill out your copyright notice in the Description page of Project Settings.


#include "HealItem.h"
#include "../BasePawn.h"


void UHealItem::Use(class ABasePawn* character)
{
    if (character)
    {
        character->health->SetHealth(character->health->GetHealth() + HealthToHeal);
    }
}

