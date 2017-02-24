// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDowm/PickupBase.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AAmmoPickup : public APickupBase
{
	GENERATED_BODY()
	
public:

	virtual void OnInteract_Implementation(AActor* Caller) override;

protected:



private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 AmmoAmount = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType = EAmmoType::AT_Bullets;
	
};
