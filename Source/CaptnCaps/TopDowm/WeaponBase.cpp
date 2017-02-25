// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WeaponBase.h"
#include "MyPlayer.h"

void AWeaponBase::AddAmmo(int32 Amount)
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, CurrentAmmo, MaxAmmo);
}

void AWeaponBase::DealDamage()
{

}

void AWeaponBase::Fire()
{

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

void AWeaponBase::SpawnImpactEffect()
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
