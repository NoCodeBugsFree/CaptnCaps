// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveGameState.h"
#include "Net/UnrealNetwork.h"

// GetLifetimeReplicatedProps
void AWaveGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaveGameState, EnemiesRemaining);
	DOREPLIFETIME(AWaveGameState, bIsActive);
	DOREPLIFETIME(AWaveGameState, WaveDelay);
	DOREPLIFETIME(AWaveGameState, MaxWaves);
	DOREPLIFETIME(AWaveGameState, CurrentWave);
}


