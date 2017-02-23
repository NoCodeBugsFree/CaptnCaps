// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class AInteractableActor;

UCLASS()
class CAPTNCAPS_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	AInteractableActor* FindFocusedActor();

private:

	UPROPERTY()
	AInteractableActor* FocusedActor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 300.f;

	FCollisionQueryParams TraceParams;


	UFUNCTION()
	void HandleHighLight();

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void LookPitch(float Value);

	UFUNCTION()
	void LookYaw(float Value);

	UFUNCTION()
	void Use();
	
};
