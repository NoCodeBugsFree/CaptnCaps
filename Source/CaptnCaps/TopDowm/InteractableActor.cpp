// Fill out your copyright notice in the Description page of Project Settings.
#include "CaptnCaps.h"
#include "InteractableActor.h"
#include "MyPlayer.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bCanInteract = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetSphereRadius(250.f);

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnOverlapEnd);

}

void AInteractableActor::BeginPlay()
{
 	Super::BeginPlay();
	// TODO test this in PostInitializeComponents or OnConstruction
 	for (auto Mesh : GetComponentsByClass(UMeshComponent::StaticClass()))
 	{
 		auto MeshToAdd = Cast<UMeshComponent>(Mesh);
 			if (MeshToAdd)
 			{
 				Meshes.Push(MeshToAdd);
				MeshToAdd->SetCustomDepthStencilValue(static_cast<int32>(Color));
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
		UE_LOG(LogTemp, Error, TEXT("AInteractableActor::OnInteract_Implementation"));
		Destroy();
 	}
}

void AInteractableActor::OnBeginFocus()
{
	if (bCanInteract)
	{
		for (UMeshComponent* Mesh : Meshes)
		{
			Mesh->SetRenderCustomDepth(true);
		}
	}
}

void AInteractableActor::OnEndFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AInteractableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(OtherActor);
	if (MyPlayer)
	{
		OnBeginFocus();
	}
	
}

void AInteractableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(OtherActor);
	if (MyPlayer)
	{
		OnEndFocus();
	}
}
