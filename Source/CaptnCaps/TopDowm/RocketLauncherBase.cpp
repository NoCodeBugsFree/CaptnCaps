// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "RocketLauncherBase.h"
#include "ProjectileBase.h"
#include "MyPlayer.h"

void ARocketLauncherBase::DoFire()
{
	FVector Location = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FRotator Rotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);

	if (ProjectileClass)
	{
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);

		if (Projectile)
		{
			Projectile->SetOwner(this);
			Projectile->Instigator = OwningPlayer;
			Projectile->Initialize(Rotation.Vector());
			SpawnFireEffect();
			CurrentAmmo--;
		}
	}

}
