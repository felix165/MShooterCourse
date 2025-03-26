// Fill out your copyright notice in the Description page of Project Settings.


#include "MShooterGameMode.h"
#include "MShooterCourse/Character/MSCharacter.h"
#include "MShooterCourse/PlayerController/MSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"

void AMShooterGameMode::PlayerEliminated(AMSCharacter* ElimmedCharacter, AMSPlayerController* VictimController, AMSPlayerController* AttackerController)
{
    if (ElimmedCharacter)
    {
        ElimmedCharacter->Elim();
    }
}

void AMShooterGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
    if (ElimmedCharacter)
    {
        ElimmedCharacter->Reset();
        ElimmedCharacter->Destroy();
    }

    if (ElimmedController)
    {
        TArray<AActor*> PlayerStarts;
        UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
        int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
        RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);
    }
}
