// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(BulletMesh);
	BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	BulletMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn , ECollisionResponse::ECR_Ignore);
	BulletMesh->SetSimulatePhysics(true);
	BulletMesh->SetEnableGravity(true);
	BulletMesh->SetNotifyRigidBodyCollision(true);
	ShellEjectionImpulse = 10.f;
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	BulletMesh->OnComponentHit.AddDynamic(this, &ABulletShell::OnHit);
	BulletMesh->AddImpulse(GetActorForwardVector() * ShellEjectionImpulse);

	SetLifeSpan(5.f);

	
}

void ABulletShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	//Destroy();
}


