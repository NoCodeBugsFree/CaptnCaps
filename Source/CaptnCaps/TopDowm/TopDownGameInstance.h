// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "TopDownGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API UTopDownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	FString LastSaveLoaded;

	bool bShouldLoadSave = false;

protected:



private:
	
	
};
