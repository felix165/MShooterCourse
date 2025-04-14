// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharOverlay.generated.h"

/**
 * 
 */
UCLASS()
class MSHOOTERCOURSE_API UCharOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* HealthText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreAmount;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DefeatsAmount;
};
