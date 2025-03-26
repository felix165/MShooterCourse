// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MSHOOTERCOURSE_API AMShooterGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PlayerEliminated(class AMSCharacter* ElimmedCharacter, class AMSPlayerController* VictimController, AMSPlayerController* AttackerController);

	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);
};
