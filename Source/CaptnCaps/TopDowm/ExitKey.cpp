// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "ExitKey.h"
#include "MyPlayer.h"


// Sets default values
AExitKey::AExitKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AExitKey::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AExitKey::OnOverlapBegin);
}

// Called every frame
void AExitKey::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AExitKey::OnInteract_Implementation(AActor* Caller)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(Caller);
	if (MyPlayer)
	{
		MyPlayer->SetHasKey(true);
		Destroy();
	}
}

void AExitKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		OnInteract(OtherActor);
	}
}

