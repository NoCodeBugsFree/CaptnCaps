// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "AmmoPickup.h"
#include "MyPlayer.h"

void AAmmoPickup::OnInteract_Implementation(AActor* Caller)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Caller);
	if (MyPlayer)
	{
		MyPlayer->AddAmmo(AmmoAmount, AmmoType);
	}
	Destroy();
}
