// Fill out your copyright notice in the Description page of Project Settings.


#include "MSAnimInstance.h"
#include "MSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	MSCharacter = Cast<AMSCharacter>(TryGetPawnOwner());

}

void UMSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (MSCharacter == nullptr)
	{
		MSCharacter = Cast<AMSCharacter>(TryGetPawnOwner());
	}
	if (MSCharacter == nullptr) return;

	FVector Velocity = MSCharacter->GetVelocity();
	Velocity.Z = 0;
	Speed = Velocity.Size();
	bIsInAir = MSCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MSCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
