// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "WaveInteractableActor.h"
#include "WaveCharacter.h"

// Sets default values
AWaveInteractableActor::AWaveInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	bTouchInteracts = true;
	bCanInteract = true;

}

// Called when the game starts or when spawned
void AWaveInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaveInteractableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWaveInteractableActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/** Fill the Meshes Array  */
	for (UActorComponent* Mesh : GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* ThisMesh = Cast<UMeshComponent>(Mesh);
		if (ThisMesh)
		{
			Meshes.Push(ThisMesh);
		}
	}
	
	if (bTouchInteracts)
	{
		OnActorBeginOverlap.AddDynamic(this, &AWaveInteractableActor::OnOverlapBegin);
	}
}

void AWaveInteractableActor::OnInteract_Implementation(AActor* Caller)
{
	// simple destroy here ...
	if (bCanInteract)
	{
		Destroy();
	}
}

void AWaveInteractableActor::OnBeginFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(true);
		Mesh->SetCustomDepthStencilValue((uint32)StencilColor);
	}
}

void AWaveInteractableActor::OnEndFocus()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(false);
	}
}

void AWaveInteractableActor::SetCanInteract(bool NewInteract)
{
	bCanInteract = NewInteract;
}

void AWaveInteractableActor::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AWaveCharacter* WaveCharacter = Cast<AWaveCharacter>(OtherActor);
	if (WaveCharacter)
	{
		OnInteract(WaveCharacter);
	}
}

