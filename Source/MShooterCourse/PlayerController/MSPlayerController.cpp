// Fill out your copyright notice in the Description page of Project Settings.


#include "MSPlayerController.h"
#include "MShooterCourse/HUD/MSHUD.h"
#include "MShooterCourse/HUD/CharOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"



void AMSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    MSHUD = Cast<AMSHUD>(GetHUD());
}

void AMSPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
    MSHUD = MSHUD == nullptr ? Cast<AMSHUD>(GetHUD()) : MSHUD;

    bool bHUDValid = MSHUD &&
        MSHUD->CharacterOverlay &&
        MSHUD->CharacterOverlay->HealthBar &&
        MSHUD->CharacterOverlay->HealthText;
    if (bHUDValid)
    {
        const float HealthPercent = Health / MaxHealth;
        MSHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
        FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
        MSHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
    }

}
