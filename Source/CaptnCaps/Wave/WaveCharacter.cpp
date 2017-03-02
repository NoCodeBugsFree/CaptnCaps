// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveCharacter.h"
#include "WaveInteractableActor.h"
#include "WaveInteractableCharacter.h"

AWaveCharacter::AWaveCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPSCamera->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TPSCamera->SetupAttachment(CameraBoom);
	TPSCamera->bAutoActivate = false;

	bIsInFPS = true;
	bAllowInput = true;
	bCrouched = false;
	bCanInteract = false;
	
	TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), false, this);

	// GetCapsuleComponent()->InitCapsuleSize(DefaultCapsuleRadius, DefaultCapsuleHalfHeight);
}

void AWaveCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpeedCorff = StandingSpeedCoeff;
}

void AWaveCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Controller && Controller->IsLocalController())
	{
		Bearing = GetActorRotation().Yaw;
		HandleFocus();
		Pitch = Controller->GetControlRotation().Pitch;
		if (Pitch > 180)
		{
			Pitch -= 360;
		}
	}
}

void AWaveCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AWaveCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AWaveCharacter::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &AWaveCharacter::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AWaveCharacter::LookPitch);

	InputComponent->BindAction("CameraSwitch", IE_Pressed, this, &AWaveCharacter::SwitchCamera);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AWaveCharacter::MyCrouch);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AWaveCharacter::Interact);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AWaveCharacter::Jump);
}

void AWaveCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWaveCharacter::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Error, TEXT("AWaveCharacter::OnInteract_Implementation"));
}

AActor* AWaveCharacter::GetFocusedActor()
{
	if (!Controller)
	{
		return nullptr;
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	FHitResult Hit(ForceInit);

	Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);

	float DistanceCameraHead = FMath::Abs( (CameraLocation - GetMesh()->GetSocketLocation(HeadSocketName)).Size());

	const FVector Start = CameraLocation;
	const FVector End = Start + (CameraRotation.Vector() * (InteractionDistance + DistanceCameraHead) );

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

	if (Hit.GetActor())
	{
		return Hit.GetActor();
	}

	return nullptr;
}

void AWaveCharacter::HandleFocus()
{
	AWaveInteractableActor* Interactable = Cast<AWaveInteractableActor>(GetFocusedActor());
	if (Interactable)
	{
		if (Interactable != FocusedActor)
		{
			if (FocusedActor)
			{
				FocusedActor->OnEndFocus();
			}
			Interactable->OnBeginFocus();
			FocusedActor = Interactable;
		}
	}
	else
	{
		if (FocusedActor)
		{
			FocusedActor->OnEndFocus();
		}
		FocusedActor = nullptr;
	}
}

void AWaveCharacter::MoveForward(float Value)
{
	if (bAllowInput)
	{
		FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, SpeedCorff * Value);
	}
}

void AWaveCharacter::MoveRight(float Value)
{
	if (bAllowInput)
	{
		FRotator Rotation(0.f, GetControlRotation().Yaw, 0.f);
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, SpeedCorff * Value);
	}
}

void AWaveCharacter::LookPitch(float Value)
{
	if (bAllowInput)
	{
		AddControllerPitchInput(Value);
	}
}

void AWaveCharacter::LookYaw(float Value)
{
	if (bAllowInput)
	{
		AddControllerYawInput(Value);
	}
}

void AWaveCharacter::SwitchCamera()
{
	if (bAllowInput)
	{
		if (bIsInFPS)
		{
			bIsInFPS = false;
			FPSCamera->Deactivate();
			TPSCamera->Activate();
		}
		else
		{
			bIsInFPS = true;
			TPSCamera->Deactivate();
			FPSCamera->Activate();
		}
	}
}

void AWaveCharacter::MyCrouch()
{
	if (bAllowInput)
	{
		if (bCrouched)
		{
			EnterCrouch();
		}
		else
		{
			ExitCrouch();
		}
	}
}

void AWaveCharacter::EnterCrouch()
{
	bCrouched = true;

	GetCapsuleComponent()->SetCapsuleSize(CrouchedCapsuleRadius, CrouchedCapsuleHalfHeight, true);

	FVector Offset = FVector(0, 0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight);
	AddActorWorldOffset(Offset);
	FPSCamera->AddRelativeLocation(Offset);
	CameraBoom->AddRelativeLocation(Offset);

	GetMesh()->AddRelativeLocation(FVector(0,0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight));
	SpeedCorff = CrouchedSpeedCoeff;
}

void AWaveCharacter::ExitCrouch()
{
	FHitResult Hit(ForceInit);
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0,0, CrouchedCapsuleHalfHeight + DefaultCapsuleRadius);

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	if (!Hit.bBlockingHit)
	{
		bCrouched = false;

		GetCapsuleComponent()->SetCapsuleSize(DefaultCapsuleRadius, DefaultCapsuleHalfHeight, true);

		FVector ReverseOffset = FVector(0,0, DefaultCapsuleHalfHeight - CrouchedCapsuleHalfHeight);
		AddActorWorldOffset(ReverseOffset);
		FPSCamera->AddRelativeLocation(ReverseOffset);
		CameraBoom->AddRelativeLocation(ReverseOffset);

		GetMesh()->AddRelativeLocation(FVector(0,0, CrouchedCapsuleHalfHeight - DefaultCapsuleHalfHeight));
		SpeedCorff = StandingSpeedCoeff;
	}
}

void AWaveCharacter::Interact()
{
	if (bAllowInput)
	{
		AActor* Focused = GetFocusedActor();
		if (Focused)
		{
			if (Focused->IsA(AWaveInteractableActor::StaticClass()))
			{
				AWaveInteractableActor* WaveInteractableActor = Cast<AWaveInteractableActor>(Focused);
				WaveInteractableActor->OnInteract(this);
			}
			else if (Focused->IsA(AWaveInteractableCharacter::StaticClass()))
			{
				AWaveInteractableCharacter* WaveInteractableCharacter = Cast<AWaveInteractableCharacter>(Focused);
				WaveInteractableCharacter->OnInteract(this);
			}
		}
	}
}

void AWaveCharacter::Jump()
{
	if (bAllowInput)
	{
		if (GetCharacterMovement()->IsMovingOnGround())
		{
			GetCharacterMovement()->DoJump(true);
			bJumping = true;
		}
	}
}

