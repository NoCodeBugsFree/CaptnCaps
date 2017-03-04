// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave/WaveCharacter.h"
#include "WavePlayer.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWavePlayer : public AWaveCharacter
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Client, Reliable)
	void UpdateHUD();

	UFUNCTION(BlueprintImplementableEvent, Category = "AAA")
	void BP_UpdateHUD();

protected:



private:
	
	
};
