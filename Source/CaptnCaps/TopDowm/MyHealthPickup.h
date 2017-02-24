// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "MyHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AMyHealthPickup : public APickupBase
{
	GENERATED_BODY()

public:

	virtual void OnInteract_Implementation(AActor* Caller) override;


protected:



private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float HealthAmount = 25.f;
	
	
};
