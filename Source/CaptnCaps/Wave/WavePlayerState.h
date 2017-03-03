// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "WavePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWavePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	void AddMoney(int32 Amount) { Money += Amount; }

	UFUNCTION(BlueprintCallable, Category = "AAA")
	int32 GetMoney() const { return Money; }

protected:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
	UPROPERTY(Replicated)
	int32 Money;
};
