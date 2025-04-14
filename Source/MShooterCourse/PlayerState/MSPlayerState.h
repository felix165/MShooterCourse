// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MSHOOTERCOURSE_API AMSPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
    virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

    /**
    * Replication notifies
    */
    virtual void OnRep_Score() override;

    UFUNCTION()
    virtual void OnRep_Defeats();

    void AddToScore(float ScoreAmount);
    void AddToDefeats(int32 DefeatsAmount);

private:
    UPROPERTY()
    class AMSCharacter* Character;
    UPROPERTY()
    class AMSPlayerController* PC;

    UPROPERTY(ReplicatedUsing = OnRep_Defeats)
    int32 Defeats;
};
