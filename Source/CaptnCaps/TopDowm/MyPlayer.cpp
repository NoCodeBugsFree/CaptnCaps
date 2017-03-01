// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "MyPlayer.h"
#include "InteractableActor.h"
#include "AssaultRifleBase.h"
#include "LaserRifleBase.h"
#include "RocketLauncherBase.h"
#include "WeaponBase.h"
#include "TopDownSaveGame.h"
#include "TopDownGameInstance.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TraceParams = FCollisionQueryParams(TEXT("TraceParams"), false, this);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.f;

	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->RelativeRotation = FRotator(-90.f, 0.f, 0.f);

	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	UTopDownGameInstance* TopDownGameInstance = Cast<UTopDownGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (TopDownGameInstance && TopDownGameInstance->bShouldLoadSave)
	{
		TopDownGameInstance->bShouldLoadSave = false;
		UTopDownSaveGame* TopDownSaveGame = UTopDownSaveGame::CreateSaveGameInstance();
		TopDownSaveGame = TopDownSaveGame->Load(TopDownGameInstance->LastSaveLoaded, 0);
		SetDataFromSave(TopDownSaveGame->SaveInfo);
	}
	else
	{
		HealthPoints = MaxHealthPoints;
	}
	
	HUDUpdateHP();
}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// HighLight only for this particular player
	if (Controller && Controller->IsLocalController())
	{
		HandleHighLight();
		GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("HP: %f"), HealthPoints));
		
		RotateCharacterTowardsMouseCursor();
	}
}

void AMyPlayer::RotateCharacterTowardsMouseCursor()
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		FVector WorldLocation, WorldDirection;

		// bool APlayerController::DeprojectMousePositionToWorld(FVector & WorldLocation, FVector & WorldDirection)
		// Convert current mouse 2D position to World Space 3D position and direction. Returns false if unable to determine value.
		PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		FRotator NewRotation = WorldDirection.Rotation();
		SetActorRotation(FRotator(0.f, NewRotation.Yaw, 0.f));
		Bearing = NewRotation.Yaw;
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);

	InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);
	InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
	InputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::StopRun);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMyPlayer::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AMyPlayer::StopFire);

	InputComponent->BindAction("SwitchToAssault", IE_Pressed, this, &AMyPlayer::SwitchToAssault);
	InputComponent->BindAction("SwitchToLaser", IE_Pressed, this, &AMyPlayer::SwitchToLaser);
	InputComponent->BindAction("SwitchToRocket", IE_Pressed, this, &AMyPlayer::SwitchToRocket);

	InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);
}

float AMyPlayer::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = 0.f; // = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
 	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
 	{
 		const FRadialDamageEvent& RadialDamageEvent = *(FRadialDamageEvent*)&DamageEvent;
		
		float MinDamage = RadialDamageEvent.Params.MinimumDamage;
		float MaxDamage  = RadialDamageEvent.Params.BaseDamage;
		float Distance = (GetActorLocation() - RadialDamageEvent.Origin).Size();
		 
		float LerpConst = Distance / RadialDamageEvent.Params.OuterRadius;
		ActualDamage = FMath::Lerp(MaxDamage, MinDamage, LerpConst);
 	}
	else
	{
		ActualDamage = DamageAmount;
		//ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

	
	HealthPoints -= ActualDamage;
	HUDUpdateHP();
	if (HealthPoints <= 0)
	{
		OnDeath();
	}

	return ActualDamage;
}

AInteractableActor* AMyPlayer::FindFocusedActor()
{
	if (!Controller)
	{
		return nullptr;
	}

	FVector Location;
	FRotator Rotation;
	FHitResult Hit(ForceInit);

	// virtual void GetPlayerViewPoint (FVector & Location, FRotator & Rotation)
	// Returns Player's Point of View For the AI this means the Pawn's 'Eyes' ViewPoint 
	// For a Human player, this means the Camera's ViewPoint
	// out_Location, view location of player out_rotation, view rotation of player
	Controller->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + GetActorForwardVector() * InteractionDistance;

	// race a ray against the world using a specific channel and return the first blocking hit
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);
	
	if (Hit.bBlockingHit)
	{
		AInteractableActor* InteractableActor = Cast<AInteractableActor>(Hit.GetActor());
		if (InteractableActor)
		{
			return InteractableActor;
		}
	}

	return nullptr;
}

void AMyPlayer::OnDeath()
{
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("You died!")));
	Destroy();
}

void AMyPlayer::Heal(float Amount)
{
	if (Amount > 0)
	{
		HealthPoints += Amount;
		if (HealthPoints > MaxHealthPoints)
		{
			HealthPoints = MaxHealthPoints;
		}
		HUDUpdateHP();
	}
}

void AMyPlayer::AddAmmo(int32 AmmoAmount, EAmmoType AmmoType)
{
	switch (AmmoType)
	{
		case EAmmoType::AT_Bullets :
		{
			if (Inventory.AssaultRifle)
			{
				Inventory.AssaultRifle->AddAmmo(AmmoAmount);
			}
			break;
		}

		case EAmmoType::SC_Lasers:
		{
			if (Inventory.LaserRifle)
			{
				Inventory.LaserRifle->AddAmmo(AmmoAmount);
			}
			break;
		}

		case EAmmoType::SC_Rockets:
		{
			if (Inventory.RocketLauncher)
			{
				Inventory.RocketLauncher->AddAmmo(AmmoAmount);
			}
			break;
		}
	}
}

void AMyPlayer::HandleHighLight()
{
	AInteractableActor* NewHighLight = FindFocusedActor();

	if (NewHighLight)
	{
		if (NewHighLight != FocusedActor)
		{
			if (FocusedActor)
			{
				FocusedActor->OnEndFocus();
			}
			
			NewHighLight->OnBeginFocus();
			FocusedActor = NewHighLight;
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

void AMyPlayer::MoveForward(float Value)
{
	// TODO correct clamp when MoveForward() and  MoveRight() functions called simultaneously
	// FVector ForwardVector = GetActorForwardVector(); 
	FVector ForwardVector(1.f, 0.f, 0.f); 
	AddMovementInput(ForwardVector, Value);
}

void AMyPlayer::MoveRight(float Value)
{
	// TODO correct clamp when MoveForward() and  MoveRight() functions called simultaneously
	//FVector RightVector = GetActorRightVector(); // FPS TPS
	FVector RightVector(0.f, 1.f, 0.f);
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

void AMyPlayer::AddToInventory(AWeaponBase* NewWeapon)
{
	if (NewWeapon)
	{
		NewWeapon->SetCanInteract(false);
		NewWeapon->SetActorEnableCollision(false);
		NewWeapon->ChangeOwner(this);
		NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		NewWeapon->SetActorHiddenInGame(true);

		// generic functions required
		if ( NewWeapon->IsA(AAssaultRifleBase::StaticClass()) )
		{
			if (Inventory.AssaultRifle)
			{
				Inventory.AssaultRifle->Destroy();
			}
			Inventory.AssaultRifle = Cast<AAssaultRifleBase>(NewWeapon);

			if ( ! Inventory.CurrentWeapon || bEquipNewWeapon)
			{
				EquipWeapon(Inventory.AssaultRifle);
			}
		}
		else if ( NewWeapon->IsA(ALaserRifleBase::StaticClass()) )
		{
			if (Inventory.LaserRifle)
			{
				Inventory.LaserRifle->Destroy();
			}
			Inventory.LaserRifle = Cast<ALaserRifleBase>(NewWeapon);

			if (!Inventory.CurrentWeapon || bEquipNewWeapon)
			{
				EquipWeapon(Inventory.LaserRifle);
			}
		} 
		else if (NewWeapon->IsA(ARocketLauncherBase::StaticClass()))
		{
			if (Inventory.RocketLauncher)
			{
				Inventory.RocketLauncher->Destroy();
			}
			Inventory.RocketLauncher = Cast<ARocketLauncherBase>(NewWeapon);

			if (!Inventory.CurrentWeapon || bEquipNewWeapon)
			{
				EquipWeapon(Inventory.RocketLauncher);
			}
		}
	}
}

void AMyPlayer::EquipWeapon(class AWeaponBase* WeaponToEquip)
{
	if (WeaponToEquip == Inventory.CurrentWeapon)
	{
		return;
	} 
	
	if (Inventory.CurrentWeapon)
	{
		Inventory.CurrentWeapon->SetActorHiddenInGame(true);
	}

	if (WeaponToEquip == Inventory.AssaultRifle)
	{
		Inventory.CurrentWeapon = Inventory.AssaultRifle;
	} 
	else if(WeaponToEquip == Inventory.LaserRifle)
	{
		Inventory.CurrentWeapon = Inventory.LaserRifle;
	}
	else if (WeaponToEquip == Inventory.RocketLauncher)
	{
		Inventory.CurrentWeapon = Inventory.RocketLauncher;
	}

	Inventory.CurrentWeapon->SetActorHiddenInGame(false);
}

void AMyPlayer::SwitchToAssault()
{
	if (Inventory.AssaultRifle)
	{
		EquipWeapon(Inventory.AssaultRifle);
	}
}

void AMyPlayer::SwitchToLaser()
{
	if (Inventory.LaserRifle)
	{
		EquipWeapon(Inventory.LaserRifle);
	}
}

void AMyPlayer::SwitchToRocket()
{
	if (Inventory.RocketLauncher)
	{
		EquipWeapon(Inventory.RocketLauncher);
	}
}

void AMyPlayer::StartFire()
{
	if (Inventory.CurrentWeapon)
	{
		Inventory.CurrentWeapon->StartFire();
	}
}

void AMyPlayer::StopFire()
{
	if (Inventory.CurrentWeapon)
	{
		Inventory.CurrentWeapon->StopFire();
	}
}

void AMyPlayer::SetDataFromSave(const FSaveGameStruct& SaveData)
{
	HealthPoints = SaveData.Health;

	// TODO Separate Function?
	if (SaveData.AssaultRifle.WeaponClass)
	{
		AWeaponBase* AssaultRifle = GetWorld()->SpawnActor<AWeaponBase>(SaveData.AssaultRifle.WeaponClass);
		if (AssaultRifle)
		{
			AssaultRifle->bSpawnFull = false;
			AssaultRifle->SetAmmo(SaveData.AssaultRifle.Ammo);
			AddToInventory(AssaultRifle);
		}
	}

	if (SaveData.LaserRifle.WeaponClass)
	{
		AWeaponBase* LaserRifle = GetWorld()->SpawnActor<AWeaponBase>(SaveData.LaserRifle.WeaponClass);
		if (LaserRifle)
		{
			LaserRifle->bSpawnFull = false;
			LaserRifle->SetAmmo(SaveData.AssaultRifle.Ammo);
			AddToInventory(LaserRifle);
		}
	}

	if (SaveData.RocketLauncher.WeaponClass)
	{
		AWeaponBase* RocketLauncher = GetWorld()->SpawnActor<AWeaponBase>(SaveData.RocketLauncher.WeaponClass);
		if (RocketLauncher)
		{
			RocketLauncher->bSpawnFull = false;
			RocketLauncher->SetAmmo(SaveData.AssaultRifle.Ammo);
			AddToInventory(RocketLauncher);
		}
	}

	switch (SaveData.CurrentWeapon)
	{
		case 1: SwitchToAssault(); break;
		case 2: SwitchToLaser(); break;
		case 3: SwitchToRocket(); break;
	}
}

FSaveGameStruct AMyPlayer::GetDataForSave()
{
	FSaveGameStruct SaveData;
	SaveData.Health = HealthPoints;

	// TODO may be an additional variable ?
	SaveData.CurrentWeapon = Inventory.CurrentWeapon == Inventory.AssaultRifle ? 1 :
		Inventory.CurrentWeapon == Inventory.LaserRifle ? 2 :
		Inventory.CurrentWeapon == Inventory.RocketLauncher ? 3 : 0;
	
	// TODO for each ? 
	if (Inventory.AssaultRifle)
	{
		SaveData.AssaultRifle.WeaponClass = Inventory.AssaultRifle->GetClass();
		SaveData.AssaultRifle.Ammo = Inventory.AssaultRifle->GetCurrentAmmo();
	}

	if (Inventory.LaserRifle)
	{
		SaveData.LaserRifle.WeaponClass = Inventory.LaserRifle->GetClass();
		SaveData.LaserRifle.Ammo = Inventory.LaserRifle->GetCurrentAmmo();
	}

	if (Inventory.RocketLauncher)
	{
		SaveData.RocketLauncher.WeaponClass = Inventory.RocketLauncher->GetClass();
		SaveData.RocketLauncher.Ammo = Inventory.RocketLauncher->GetCurrentAmmo();
	}
	
	return SaveData;
}

void AMyPlayer::SpawnInventory(const FSaveGameStruct& SaveData)
{

}

void AMyPlayer::Use()
{
	AInteractableActor* InteractableActor = FindFocusedActor();
	if (InteractableActor)
	{
		InteractableActor->OnInteract(this);
	}
}

void AMyPlayer::StartRun()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyPlayer::StopRun()
{
	bIsRunning = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

