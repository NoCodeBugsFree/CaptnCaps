// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WeaponBase.h"
#include "MyPlayer.h"

AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);

	TraceParams = FCollisionQueryParams( FName(TEXT("ProjectileTrace")), true, this );
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;
}

void AWeaponBase::AddAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, CurrentAmmo, MaxAmmo);
}

void AWeaponBase::DealDamage(const FHitResult& Hit)
{

}

void AWeaponBase::StartFire()
{
	if (CurrentAmmo > 0)
	{
		DoFire();
		float TimerDelay = FireRate > 0 ? 1 / (FireRate * 0.01667) : FApp::GetDeltaTime(); // GetWorld()->DeltaTimeSeconds

		auto World = GetWorld();
		if (World)
		{
			if (!FireRateHandle.IsValid())
			{
				World->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::StartFire, TimerDelay, true);
			}
		}
	}
	else
	{
		StopFire();
	}
}

void AWeaponBase::StopFire()
{
	auto World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(FireRateHandle);
		FireRateHandle.Invalidate();
	}
}

void AWeaponBase::DoFire()
{
	FHitResult Hit(ForceInit);
	FVector Start;
	if (WeaponMesh)
	{
		Start = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	}
	else
	{
		Start = GetActorLocation();
	}
	
	FVector End = Start + CalcSpread() * MaxRange;

	auto World = GetWorld();
	if (World)
	{
		World->LineTraceSingleByChannel(Hit, Start, End, ECC_Weapon, TraceParams);
		DrawDebugLine(World, Start, End, FColor::Red, false, 15.f, 0, 2.f);
	}
	
	CurrentAmmo--;
	SpawnFireEffect();
	

	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Error, TEXT("You Hit %s!"), *Hit.GetActor()->GetName());
		DealDamage(Hit);
		SpawnImpactEffect(Hit);
	}
}

FVector AWeaponBase::CalcSpread()
{
	if (OwningPlayer)
	{
		FVector ForwardVector = OwningPlayer->GetActorForwardVector();

		// Spread at 10 000 - 100 meters
		float Angle = FMath::RadiansToDegrees( atan( Spread / 10000 ) );

		// Returns a random unit vector, uniformly distributed, within the specified cone 
		// ConeHalfAngleRad is the half - angle of cone, in radians.Returns a normalized vector.
		return FMath::VRandCone(ForwardVector, Angle);
	}
	else
	{
		FVector ForwardVector = GetActorForwardVector();
		float Angle = FMath::RadiansToDegrees(atan(Spread / 10000));
		return FMath::VRandCone(ForwardVector, Angle);
	}
}

void AWeaponBase::SpawnFireEffect()
{
	// TODO
}

void AWeaponBase::SpawnImpactEffect(const FHitResult& Hit)
{
	// TODO
}

void AWeaponBase::OnInteract_Implementation(AActor* Caller)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Caller);
	if (MyPlayer)
	{
		MyPlayer->AddToInventory(this);
	}
}

void AWeaponBase::ChangeOwner(AActor* NewOwner)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(NewOwner);
	if (MyPlayer)
	{
		OwningPlayer = MyPlayer;
	}
	SetOwner(NewOwner);
}
