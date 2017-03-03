// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveGameMode.h"
#include "WaveEnemy.h"
#include "WaveGameState.h"
#include "WavePlayerState.h"
#include "WaveInteractableActor.h"

AWaveGameMode::AWaveGameMode()
{

}

void AWaveGameMode::InitGameState()
{
	Super::InitGameState();

	WaveGameState = Cast<AWaveGameState>(UGameplayStatics::GetGameState(this));
	if (WaveGameState)
	{
		WaveGameState->SetMaxWaves(MaxWaves);
		WaveGameState->SetWaveDelay(WaveDelay);
	}
}

void AWaveGameMode::BeginPlay()
{
	Super::BeginPlay();

	InitializeTaggedSpawnPoints();

}

void AWaveGameMode::InitializeTaggedSpawnPoints()
{
	TArray<AActor*> Spawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Spawns);
	for (AActor* Spawn : Spawns)
	{
		if (Spawn && Spawn->ActorHasTag(SpawnTag))
		{
			AISpawnPoints.Add(Spawn);
		}
	}
}

void AWaveGameMode::Killed(AController* Killer, AController* Victim)
{
	if (!Killer || ! Victim)
	{
		return;
	}

	AWaveInteractableCharacter* VictimPawn = Cast<AWaveInteractableCharacter>(Victim->GetPawn());
	if (VictimPawn && !VictimPawn->IsPlayerControlled()) // AI checking
	{
		if (WaveGameState)
		{
			WaveGameState->AddEnemiesRemaining(-1);
		}
	}

	AWavePlayerState* WavePlayerState = Cast<AWavePlayerState>(Killer->PlayerState);
	if (WavePlayerState)
	{
		WavePlayerState->AddMoney(10); // TODO valid number
	}

	if (WaveGameState && WaveGameState->GetEnemiesRemaining() <= 0)
	{
		EndWave();
	}
}

void AWaveGameMode::BeginWave()
{
	// ClearTimer
	auto World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(WaveTimerHandle);
		WaveTimerHandle.Invalidate();
	}

	if (WaveGameState)
	{
		WaveGameState->SetIsWaveActive(true);
		WaveGameState->SetCurrentWave(WaveGameState->GetCurrentWave() + 1);
		BeginSpawning();
	}
}

void AWaveGameMode::EndWave()
{
	if (WaveGameState)
	{
		WaveGameState->SetIsWaveActive(false);
		if (WaveGameState->GetCurrentWave() >= MaxWaves)
		{
			EndMatch();
		}
		else
		{
			auto World = GetWorld();
			if (World)
			{
				World->GetTimerManager().SetTimer(WaveTimerHandle, this, &AWaveGameMode::BeginWave, WaveDelay, false);
			}
		}
	}
}

void AWaveGameMode::BeginSpawning()
{
	if (WaveGameState)
	{
		SpawnedOfType.Empty();

		int32 CurrentWave = WaveGameState->GetCurrentWave();
		for (int i = 0; i < WaveInfo[CurrentWave - 1].SpawnInfo.Num(); i++)
		{
			SpawnedOfType.Add(0);
		}
		EnemyToSpawn = 0;
		EnemiesSpawned = 0;

		auto World = GetWorld();
		if (World)
		{
			World->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AWaveGameMode::SpawnEnemy, SpawnDelay, true);
		}
	}
}

void AWaveGameMode::SpawnEnemy()
{
	if (AISpawnPoints.Num() < 1 || WaveInfo.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("AISpawnPoints.Num() < 1 || WaveInfo.Num() < 1 -- AWaveGameMode::SpawnEnemy() "));
		// ClearTimer
		auto World = GetWorld();
		if (World)
		{
			World->GetTimerManager().ClearTimer(SpawnTimerHandle);
			SpawnTimerHandle.Invalidate();
		}
	}

	if (WaveGameState)
	{
		int32 CurrentWave = WaveGameState->GetCurrentWave();
		if (EnemiesSpawned < WaveInfo[CurrentWave - 1].TotalNumberOfEnemies)
		{
			// Spawn More
			FSpawnInfo SpawnInfo = WaveInfo[CurrentWave - 1].SpawnInfo[EnemyToSpawn];

			if (SpawnedOfType[EnemyToSpawn] < SpawnInfo.MaxEnemiesAmount)
			{
				float Prob = FMath::RandRange(0.f, 1.f);
				if (Prob <= SpawnInfo.Probability)
				{
					int32 SpawnIndex = FMath::RandRange(0, AISpawnPoints.Num() - 1);
					FVector SpawnLocation = AISpawnPoints[SpawnIndex]->GetActorLocation();
					FRotator SpawnRotation = AISpawnPoints[SpawnIndex]->GetActorRotation();

					if (SpawnInfo.EnemyClass)
					{
						GetWorld()->SpawnActor<AActor>(SpawnInfo.EnemyClass, SpawnLocation, SpawnRotation);
						EnemiesSpawned++;
						SpawnedOfType[EnemyToSpawn]++;
						if (WaveGameState)
						{
							WaveGameState->AddEnemiesRemaining(1);
						}
					}
				}
			}

			if (EnemyToSpawn >= WaveInfo[CurrentWave - 1].SpawnInfo.Num() - 1)
			{
				EnemyToSpawn = 0;
			}
			else
			{
				EnemyToSpawn++;
			}
		}
		else
		{
			auto World = GetWorld();
			if (World)
			{
				World->GetTimerManager().ClearTimer(SpawnTimerHandle);
				SpawnTimerHandle.Invalidate(); 
			}
		}
	}
}

void AWaveGameMode::StartMatch()
{
	// Returns true if the match state is InProgress or later
	if (!HasMatchStarted())
	{
		EndWave();
	}

	Super::StartMatch();
}

void AWaveGameMode::EndMatch()
{
	Super::EndMatch();
	UE_LOG(LogTemp, Error, TEXT("You won the match"));
}


