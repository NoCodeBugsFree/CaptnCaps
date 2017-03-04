// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveShop.h"
#include "WaveGameState.h"

void AWaveShop::OnInteract_Implementation(AActor* Caller)
{
	AWaveGameState* WaveGameState = GetWorld()->GetGameState<AWaveGameState>();
	if (WaveGameState && WaveGameState->IsWaveActive())
	{
		UE_LOG(LogTemp, Error, TEXT("You can't access the shop!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Welcome to the shop!"));
	}
}
