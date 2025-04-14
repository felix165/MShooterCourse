// Fill out your copyright notice in the Description page of Project Settings.


#include "MShooterGameMode.h"
#include "MShooterCourse/Character/MSCharacter.h"
#include "MShooterCourse/PlayerController/MSPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "MShooterCourse/PlayerState/MSPlayerState.h"

void AMShooterGameMode::PlayerEliminated(AMSCharacter* ElimmedCharacter, AMSPlayerController* VictimController, AMSPlayerController* AttackerController)
{
    if (AttackerController == nullptr || AttackerController->PlayerState == nullptr) return;
    if (VictimController == nullptr || VictimController->PlayerState == nullptr) return;

    AMSPlayerState* AttackerPS = AttackerController ? Cast<AMSPlayerState>(AttackerController->PlayerState) : nullptr;
    AMSPlayerState* VictimPS = VictimController ? Cast<AMSPlayerState>(VictimController->PlayerState) : nullptr;

    if (AttackerPS && AttackerPS != VictimPS)
    {
        AttackerPS->AddToScore(1.f);
    }

    if (VictimPS)
    {
        VictimPS->AddToDefeats(1);
    }


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
