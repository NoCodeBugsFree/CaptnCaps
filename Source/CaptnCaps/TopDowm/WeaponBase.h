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

	void AddAmmo(int32 Amount);

	void DealDamage();

	void Fire();

	FVector CalcSpread();

	void SpawnFireEffect();

	void SpawnImpactEffect();

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
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float Spread;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	uint32 bIsUseProjectile : 1;

	UPROPERTY(meta = (EditCondition = "bIsUseProjectile", AllowPrivateAccess = "true"), EditDefaultsOnly, BlueprintReadOnly, Category = "AAA")
	TSubclassOf<class AProjectileBase> Projectile;

private:	
	  
	
};
