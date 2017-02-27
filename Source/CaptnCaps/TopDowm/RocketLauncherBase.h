// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TopDowm/WeaponBase.h"
#include "RocketLauncherBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API ARocketLauncherBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:

	virtual void DoFire() override;
	
protected:



private:


	
	
};
