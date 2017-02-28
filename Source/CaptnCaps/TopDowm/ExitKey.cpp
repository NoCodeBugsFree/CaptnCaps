// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "ExitKey.h"


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
	
}

// Called every frame
void AExitKey::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

