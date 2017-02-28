// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "TopDownSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSaveStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	int32 Ammo;
};

USTRUCT(BlueprintType)
struct FSaveGameStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FString Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	int CurrentWeapon; // 1 - assault, 2 - laser, 3 - rocket

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FWeaponSaveStruct AssaultRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FWeaponSaveStruct LaserRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AAA")
	FWeaponSaveStruct RocketLauncher;
	
};

/**
 * 
 */
UCLASS()
class CAPTNCAPS_API UTopDownSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UTopDownSaveGame();

	static UTopDownSaveGame* CreateSaveGameInstance();

	void Save();

	UTopDownSaveGame* Load(FString Slot, uint32 Index);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FSaveGameStruct SaveInfo;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	FString SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
	int32 UserIndex;

	
private:
	
	
};
