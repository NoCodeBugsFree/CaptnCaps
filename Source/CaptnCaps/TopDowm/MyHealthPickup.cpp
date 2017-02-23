// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "MyHealthPickup.h"
#include "MyPlayer.h"

void AMyHealthPickup::OnInteract_Implementation(AActor* Caller)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Caller);
	if (MyPlayer)
	{
		MyPlayer->Heal(HealthAmount);
		Destroy();
	}
}
