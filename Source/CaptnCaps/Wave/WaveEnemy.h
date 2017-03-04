// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave/WaveInteractableCharacter.h"
#include "WaveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWaveEnemy : public AWaveInteractableCharacter
{
	GENERATED_BODY()
	
public:

	
	virtual void OnInteract_Implementation(AActor* Caller) override;

protected:



private:
	
	
};
