// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class MSHOOTERCOURSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	


private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;
};
