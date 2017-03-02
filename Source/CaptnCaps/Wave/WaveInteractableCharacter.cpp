// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveInteractableCharacter.h"


// Sets default values
AWaveInteractableCharacter::AWaveInteractableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanInteract = true;
}

// Called when the game starts or when spawned
void AWaveInteractableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveInteractableCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AWaveInteractableCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AWaveInteractableCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// GetComponentsByClass
	for (UActorComponent* MeshComp : GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* ThisMesh = Cast<UMeshComponent>(MeshComp);
		if (ThisMesh)
		{
			Meshes.Push(ThisMesh);
		}
	}
}

void AWaveInteractableCharacter::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Error, TEXT("AWaveInteractableCharacter::OnInteract_Implementation()"));
}

void AWaveInteractableCharacter::OnBeginFocus()
{
	for (UMeshComponent* MeshComp : Meshes)
	{
		MeshComp->SetRenderCustomDepth(true);
		MeshComp->SetCustomDepthStencilValue((int32)StencilColor);
	}
}

void AWaveInteractableCharacter::OnEndFocus()
{
	for (UMeshComponent* MeshComp : Meshes)
	{
		MeshComp->SetRenderCustomDepth(false);
	}
}

