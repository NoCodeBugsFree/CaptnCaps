 // Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "ExitDoor.h"
#include "MyPlayer.h"
#include "TopDownSaveGame.h"
#include "TopDownGameInstance.h"

// Sets default values
AExitDoor::AExitDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	OpenTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	OpenTrigger->SetupAttachment(RootComponent);

	LoadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LoadTrigger"));
	LoadTrigger->SetupAttachment(RootComponent);

	bShouldLerp = false;
}

// Called when the game starts or when spawned
void AExitDoor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	OpenTrigger->OnComponentBeginOverlap.AddDynamic(this, &AExitDoor::OnOverlapBegin);
	LoadTrigger->OnComponentBeginOverlap.AddDynamic(this, &AExitDoor::OnOverlapBegin);
}

// Called every frame
void AExitDoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (bShouldLerp)
	{
		// static FVector VInterpTo (const FVector& Current, const FVector& Target, float DeltaTime, float InterpSpeed)
		// Interpolate vector from Current to Target. Scaled by distance to Target, 
		// so it has a strong start speed and ease out
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewLocation, DeltaTime, LerpSpeed));
	}
}

void AExitDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyPlayer* MyPlayer = Cast<AMyPlayer>(OtherActor);

	if (OverlappedComponent == OpenTrigger && MyPlayer)
	{
		if (MyPlayer->IsPlayerHasKey())
		{
			MyPlayer->SetHasKey(false);
			NewLocation = GetActorLocation() + FVector(0.f, 0.f, 200.f);
			bShouldLerp = true;
			SetActorTickEnabled(true);
		}
	}
	else if (OverlappedComponent == LoadTrigger && MyPlayer)
	{
		UTopDownSaveGame* TopDownSaveGame = UTopDownSaveGame::CreateSaveGameInstance();

		TopDownSaveGame->SaveInfo = MyPlayer->GetDataForSave();

		// Converts an FName to a readable format, in place
		LevelToLoadName.ToString(TopDownSaveGame->SaveInfo.Level);

		TopDownSaveGame->Save();

		UTopDownGameInstance* TopDownGameInstance = Cast<UTopDownGameInstance>(GetGameInstance());
		if (TopDownGameInstance)
		{
			TopDownGameInstance->bShouldLoadSave = true;
			TopDownGameInstance->LastSaveLoaded = "Autosave";
		}

		UGameplayStatics::OpenLevel(this, LevelToLoadName, false);
	}
}

