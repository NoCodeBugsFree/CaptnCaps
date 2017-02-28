// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Particles"));
	ProjectileParticles->SetupAttachment(RootComponent);

	TraceParams = FCollisionQueryParams(FName(TEXT("ProjectileTrace")), false, this);

	InitialLifeSpan = 10.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Trace(DeltaTime);

	Move(DeltaTime);
}

void AProjectileBase::Trace(float DeltaTime)
{
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start + Velocity * DeltaTime;

	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	if (Hit.GetActor())
	{
		DealDamage(Hit);
		SpawnImpactEffect(Hit);
		Destroy();
	}
}

void AProjectileBase::DealDamage(const FHitResult& Hit)
{
	TArray<FHitResult> Hits;

	FVector Start = Hit.ImpactPoint;
	FVector End = Start + FVector(0, 0, 1);
	
	
	GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_Weapon,
		FCollisionShape::MakeSphere(RadialDamageParams.OuterRadius), TraceParams);

	FRadialDamageEvent RadialDamageEvent;
	RadialDamageEvent.Params = RadialDamageParams;
	RadialDamageEvent.Origin = Hit.ImpactPoint;
	RadialDamageEvent.ComponentHits = Hits;

	for (const FHitResult& NewHit : Hits)
	{
		if (NewHit.GetActor())
		{
			NewHit.GetActor()->TakeDamage(RadialDamageParams.BaseDamage, RadialDamageEvent, Instigator->GetController(), this);
			if (NewHit.GetComponent())
			{
				FVector Direction = NewHit.GetActor()->GetActorLocation() - RadialDamageEvent.Origin;
				Direction.Normalize();
				NewHit.GetComponent()->AddImpulse(Direction * ImpulsStrength, "", true);
			}
		}
	}
}

void AProjectileBase::SpawnImpactEffect(const FHitResult& Hit)
{
	FVector ImpactLocation = Hit.ImpactPoint;
	FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

	if (ImpactFireEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFireEffect, ImpactLocation, ImpactRotation, true);
	}

	if (ImpactFireEffectSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactFireEffectSound, ImpactLocation, ImpactRotation);
	}
}

void AProjectileBase::Initialize(FVector Direction)
{
	Velocity = Direction * InitialSpeed;
}

void AProjectileBase::Move(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
}

