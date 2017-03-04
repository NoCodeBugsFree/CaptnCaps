// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveEnemy.h"
#include "WaveGameMode.h"
#include "WavePlayer.h"

void AWaveEnemy::OnInteract_Implementation(AActor* Caller)
{
	//AWaveGameMode* WaveGameMode = Cast<AWaveGameMode>(UGameplayStatics::GetGameMode(this));
	AWaveGameMode* WaveGameMode = GetWorld()->GetAuthGameMode<AWaveGameMode>();
	if (WaveGameMode)
	{
		AWavePlayer* Killer = Cast<AWavePlayer>(Caller);
		if (Killer)
		{
			WaveGameMode->Killed(Killer->GetController(), GetController());
		}
	}

	Destroy();
}
