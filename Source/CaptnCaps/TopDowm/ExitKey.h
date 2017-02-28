// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "ExitKey.generated.h"

UCLASS()
class CAPTNCAPS_API AExitKey : public APickupBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitKey();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnInteract_Implementation(AActor* Caller) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
