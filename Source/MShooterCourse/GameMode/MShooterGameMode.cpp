// Fill out your copyright notice in the Description page of Project Settings.


#include "MShooterGameMode.h"
#include "MShooterCourse/Character/MSCharacter.h"
#include "MShooterCourse/PlayerController/MSPlayerController.h"

void AMShooterGameMode::PlayerEliminated(AMSCharacter* ElimmedCharacter, AMSPlayerController* VictimController, AMSPlayerController* AttackerController)
{
    if (ElimmedCharacter)
    {
        ElimmedCharacter->Elim();
    }
}
