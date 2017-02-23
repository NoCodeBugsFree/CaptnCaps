// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "MyPlayer.h"
#include "InteractableActor.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);

	InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);

}


AInteractableActor* AMyPlayer::FindFocusedActor()
{
	return nullptr;
}

void AMyPlayer::MoveForward(float Value)
{
	FVector ForwardVector = GetActorForwardVector();
	AddMovementInput(ForwardVector, Value);
}

void AMyPlayer::MoveRight(float Value)
{
	FVector RightVector = GetActorRightVector();
	AddMovementInput(RightVector, Value);
}

void AMyPlayer::LookPitch(float Value)
{
	AddControllerPitchInput(Value);
}

void AMyPlayer::LookYaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMyPlayer::Use()
{
	UE_LOG(LogTemp, Error, TEXT("Your message"));
	
}

