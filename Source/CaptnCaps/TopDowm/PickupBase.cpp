// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "PickupBase.h"


// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	RootComponent = PickupMesh;
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");
	

	bIsTouchInteracts = true;
	bCanInteract = true;
	
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (bIsTouchInteracts)
	{
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);
	}
}

// Called every frame
void APickupBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APickupBase::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Error, TEXT(" APickupBase::OnInteract_Implementation"));
}

void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnInteract(OtherActor);
}

