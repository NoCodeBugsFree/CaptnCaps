// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "LaserRifleBase.h"

void ALaserRifleBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// May be timer is simple ? =)
	if ( ! bIsFiring && ! IsAmmoFull() )
	{
		Charge += DeltaSeconds * RechargeAmount;
		if (Charge > 1)
		{
			AddAmmo(static_cast<uint32>(Charge));
			Charge -= 1;
		}
	}
}
