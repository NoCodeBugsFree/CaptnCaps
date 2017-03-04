// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WaveInteractableActor.generated.h"

UCLASS()
class CAPTNCAPS_API AWaveInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveInteractableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Allow actors to initialize themselves on the C++ side
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AAA")
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	void OnBeginFocus();

	void OnEndFocus();

	void SetCanInteract(bool NewInteract);

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	uint32 bCanInteract : 1;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	uint32 bTouchInteracts : 1;

	UPROPERTY(EditDefaultsOnly, Category = "AAA")
	EStencilColor StencilColor = EStencilColor::SC_Orange;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	TArray<UMeshComponent*> Meshes; // UMeshComponent - for Static or Skeletal meshes

	
};
