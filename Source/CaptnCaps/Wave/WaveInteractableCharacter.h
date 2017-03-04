// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "WaveInteractableCharacter.generated.h"

UCLASS()
class CAPTNCAPS_API AWaveInteractableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWaveInteractableCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Allow actors to initialize themselves on the C++ side
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	void OnBeginFocus();

	void OnEndFocus();
	
	void SetCanInteract(bool NewCanInteract) { bCanInteract = NewCanInteract; }

	int32 GetMoneyReward() const { return MoneyReward; }

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bCanInteract : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EStencilColor StencilColor = EStencilColor::SC_Blue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 MoneyReward = 100;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<UMeshComponent*> Meshes;
	
};
