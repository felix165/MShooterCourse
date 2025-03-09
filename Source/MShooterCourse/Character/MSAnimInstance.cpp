// Fill out your copyright notice in the Description page of Project Settings.


#include "MSAnimInstance.h"
#include "MSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "Weapon.h"

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
	bWeaponEquipped = MSCharacter->IsWeaponEquipped();
	EquippedWeapon = MSCharacter->GetEquippedWeapon();
	bIsCrouched = MSCharacter->bIsCrouched;
	bIsAiming = MSCharacter->IsAiming();
	TurningInPlace = MSCharacter->GetTurningInPlace();

	// Offset Yaw for Strafing
	FRotator AimRotation= MSCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MSCharacter->GetVelocity());
	FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
	DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, DeltaSeconds, 6.f);
	YawOffset = DeltaRotation.Yaw;

	//Lean
	CharacterRotationLastFrame = CharacterRotation;
	CharacterRotation = MSCharacter->GetActorRotation();
	const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
	const float Target = Delta.Yaw / DeltaSeconds;
	const float Interp = FMath::FInterpTo(Lean, Target, DeltaSeconds, 6.f);
	Lean = FMath::Clamp(Interp, -90.f, 90.f);

	AO_Yaw = MSCharacter->GetAO_Yaw();
	AO_Pitch = MSCharacter->GetAO_Pitch();
	

	if (bWeaponEquipped && EquippedWeapon && EquippedWeapon->GetWeaponMesh() && MSCharacter->GetMesh())
	{
		LeftHandTransform = EquippedWeapon->GetWeaponMesh()->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);

		FVector OutPosition;
		FRotator OutRotation;

		MSCharacter->GetMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), FRotator::ZeroRotator, OutPosition, OutRotation);
		LeftHandTransform.SetLocation(OutPosition);
		LeftHandTransform.SetRotation(FQuat(OutRotation));
	}
}
