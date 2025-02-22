// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMSCharacter::AMSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AMSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AMSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &AMSCharacter::Turn);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &AMSCharacter::LookUp);
}

void AMSCharacter::MoveForward(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value);
	if(Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AMSCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AMSCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);

}

void AMSCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


