// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "WaveGameState.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWaveGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//
	void SetIsWaveActive(bool NewActive) { bIsActive = NewActive; }

	void AddEnemiesRemaining(int32 Amount) { EnemiesRemaining += Amount; }

	void SetWaveDelay(float Delay) { WaveDelay = Delay; }

	void SetMaxWaves(int32 Waves) { MaxWaves = Waves; }

	void SetCurrentWave(int32 Wave) { CurrentWave = Wave; }


	// HUD
	UFUNCTION(BlueprintCallable, Category = "AAA")
	bool IsWaveActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetEnemiesRemaining() const { return EnemiesRemaining; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	float GetWaveDelay() const { return WaveDelay; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void GetWaves(int32& Max, int32& Current) const { Max = MaxWaves; Current = CurrentWave; }

	// cpp only
	int32 GetMaxWaves() const { return MaxWaves; }

	int32 GetCurrentWave() const { return CurrentWave; }

protected:



private:
	
	UPROPERTY(Replicated)
	int32 EnemiesRemaining;

	UPROPERTY(Replicated)
	uint32 bIsActive : 1;

	UPROPERTY(Replicated)
	float WaveDelay = 10.f;
	
	UPROPERTY(Replicated)
	int32 MaxWaves;

	UPROPERTY(Replicated)
	int32 CurrentWave;

};
