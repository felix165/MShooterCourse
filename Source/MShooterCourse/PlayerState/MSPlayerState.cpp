// Fill out your copyright notice in the Description page of Project Settings.


#include "MSPlayerState.h"
#include "MShooterCourse/Character/MSCharacter.h"
#include "MShooterCourse/PlayerController/MSPlayerController.h"
#include "Net/UnrealNetwork.h"

void AMSPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AMSPlayerState, Defeats, COND_OwnerOnly);
}

void AMSPlayerState::OnRep_Score()
{
    Super::OnRep_Score();

    Character = Character == nullptr ? Cast<AMSCharacter>(GetPawn()) : Character;
    if (Character && Character->Controller)
    {
        PC = PC == nullptr ? Cast<AMSPlayerController>(Character->Controller) : PC;
        if (PC)
        {
            PC->SetHUDScore(GetScore());
        }
    }
}

void AMSPlayerState::AddToScore(float ScoreAmount)
{
    SetScore(GetScore() + ScoreAmount);
    Character = Character == nullptr ? Cast<AMSCharacter>(GetPawn()) : Character;
    if (Character && Character->Controller)
    {
        PC = PC == nullptr ? Cast<AMSPlayerController>(Character->Controller) : PC;
        if (PC)
        {
            PC->SetHUDScore(GetScore());
        }
    }
}

void AMSPlayerState::OnRep_Defeats()
{
    Character = Character == nullptr ? Cast<AMSCharacter>(GetPawn()) : Character;
    if (Character && Character->Controller)
    {
        PC = PC == nullptr ? Cast<AMSPlayerController>(Character->Controller) : PC;
        if (PC)
        {
            PC->SetHUDDefeats(Defeats);
        }
    }
}

void AMSPlayerState::AddToDefeats(int32 DefeatsAmount)
{
    Defeats += DefeatsAmount;
    Character = Character == nullptr ? Cast<AMSCharacter>(GetPawn()) : Character;
    if (Character && Character->Controller)
    {
        PC = PC == nullptr ? Cast<AMSPlayerController>(Character->Controller) : PC;
        if (PC)
        {
            PC->SetHUDDefeats(Defeats);
        }
    }
}
