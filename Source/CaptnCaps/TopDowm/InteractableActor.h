// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class CAPTNCAPS_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnBeginFocus();

	UFUNCTION(BlueprintCallable, Category = "AAA")
	void OnEndFocus();
	
protected:

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bCanInteract : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<UMeshComponent*> Meshes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EStencilColor Color = EStencilColor::SC_Blue;
	
};
