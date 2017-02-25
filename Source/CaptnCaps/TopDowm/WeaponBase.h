// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API AWeaponBase : public APickupBase
{
	GENERATED_BODY()
	
public:

	AWeaponBase();

	virtual void BeginPlay() override;

	void AddAmmo(int32 Amount);

	void DealDamage(const FHitResult& Hit);

	void StartFire();
	void StopFire();

	virtual void DoFire();

	FVector CalcSpread();

	void SpawnFireEffect();

	void SpawnImpactEffect(const FHitResult& Hit);

	virtual void OnInteract_Implementation(AActor* Caller) override;

	void ChangeOwner(AActor* NewOwner);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	class AMyPlayer* OwningPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	EAmmoType AmmoType = EAmmoType::AT_Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Spread = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float BaseDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsUseProjectile : 1;

	UPROPERTY(meta = (EditCondition = "bIsUseProjectile", AllowPrivateAccess = "true"), EditDefaultsOnly, BlueprintReadOnly, Category = "AAA")
	TSubclassOf<class AProjectileBase> Projectile;

	FCollisionQueryParams TraceParams;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float FireRate = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float MaxRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FTimerHandle FireRateHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FName MuzzleSocketName = "Muzzle";

private:	
	  
	
};
