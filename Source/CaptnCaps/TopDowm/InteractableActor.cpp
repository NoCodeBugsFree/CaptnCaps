// Fill out your copyright notice in the Description page of Project Settings.
#include "CaptnCaps.h"
#include "InteractableActor.h"
#include "MyPlayer.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanInteract = true;
}

void AInteractableActor::BeginPlay()
{
 	Super::BeginPlay();
 	for (auto Mesh : GetComponentsByClass(UMeshComponent::StaticClass()))
 	{
 		auto MeshToAdd = Cast<UMeshComponent>(Mesh);
 			if (MeshToAdd)
 			{
 				Meshes.AddUnique(MeshToAdd);
 			}
 	}
}

void AInteractableActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInteractableActor::OnInteract_Implementation(AActor* Caller)
{
 	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Caller);
 	if (MyPlayer)
 	{
		
 	}
}

void AInteractableActor::OnBeginFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(true);
	}
}

void AInteractableActor::OnEndFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}
