// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(BulletMesh);

}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	
}


