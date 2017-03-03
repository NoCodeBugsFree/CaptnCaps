// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "WaveGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWaveGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	AWaveGameMode();

	virtual void BeginPlay() override;

	void InitializeTaggedSpawnPoints();


	virtual void Killed(AController* Killer, AController* Victim);

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetWaveDelay(float Delay) { WaveDelay = Delay; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetMaxWaves(int32 Max) { MaxWaves = Max; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void SetWaveInfo(const TArray<FWaveInfo>& NewWaveInfo) { WaveInfo = NewWaveInfo; }



protected:

	void BeginWave();
	
	void EndWave();
	
	void BeginSpawning();

	void SpawnEnemy();

	/** 
	 Transition from WaitingToStart to InProgress. You can call this manually, 
	 will also get called if ReadyToStartMatch returns true
	*/
	virtual void StartMatch() override;

	/** 
		Transition from InProgress to WaitingPostMatch. You can call this manually,
		will also get called if ReadyToEndMatch returns true
	*/
	virtual void EndMatch() override;

	/**
	*	Initialize the GameState actor with default settings called 
		during PreInitializeComponents() of the GameMode after 
		a GameState has been spawned as well as during Reset()
	*/
	virtual void InitGameState() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	FName SpawnTag;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float WaveDelay;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	float SpawnDelay;
	
	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	int32 MaxWaves;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	TArray<struct FWaveInfo> WaveInfo;

	int32 EnemyToSpawn;

	int32 EnemiesSpawned;

	FTimerHandle WaveTimerHandle;
	FTimerHandle SpawnTimerHandle;

	TArray<int32> SpawnedOfType;

	TArray<AActor*> AISpawnPoints;

	class AWaveGameState* WaveGameState;

};
