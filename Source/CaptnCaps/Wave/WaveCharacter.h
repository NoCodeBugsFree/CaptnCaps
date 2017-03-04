// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave/WaveInteractableCharacter.h"
#include "WaveCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWaveCharacter : public AWaveInteractableCharacter
{
	GENERATED_BODY()
	
public:

	AWaveCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Allow actors to initialize themselves on the C++ side
	virtual void PostInitializeComponents() override;

	virtual void OnInteract_Implementation(AActor* Caller) override;

	// INTERACTION
	AActor* GetFocusedActor();
	
	void HandleFocus();

	// INPUT
	void MoveForward(float Value);

	void MoveRight(float Value);

	void LookPitch(float Value);

	void LookYaw(float Value);

	void SwitchCamera();

	void MyCrouch();

	void EnterCrouch();

	void ExitCrouch();

	void Interact();

	void Jump();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPSCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TPSCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

private:
	
	float Bearing;

	float Pitch;

	float SpeedCoeff;

	class AWaveInteractableActor* FocusedActor;

	uint32 bIsInFPS : 1;

	uint32 bAllowInput : 1;

	uint32 bCrouched : 1;
	
	uint32 bJumping : 1;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float DefaultCapsuleHalfHeight;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float DefaultCapsuleRadius;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float CrouchedCapsuleHalfHeight;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float CrouchedCapsuleRadius;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float StandingSpeedCoeff;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float CrouchedSpeedCoeff;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	FName HeadSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float InteractionDistance;

	FCollisionQueryParams TraceParams;
};
