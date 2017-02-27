// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDowm/WeaponBase.h"
#include "LaserRifleBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API ALaserRifleBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaSeconds) override;

protected:



private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float RechargeAmount = 5.f;

	float Charge;
	
};
