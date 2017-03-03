// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WavePlayerState.h"
#include "Net/UnrealNetwork.h"

void AWavePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AWavePlayerState, Money);
}