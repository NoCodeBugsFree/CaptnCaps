// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave/WaveInteractableActor.h"
#include "WaveShop.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWaveShop : public AWaveInteractableActor
{
	GENERATED_BODY()
	
public:

	virtual void OnInteract_Implementation(AActor* Caller) override;

protected:



private:
	
	
};
