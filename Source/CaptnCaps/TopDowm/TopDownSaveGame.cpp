// Fill out your copyright notice in the Description page of Project Settings.

#include "CaptnCaps.h"
#include "TopDownSaveGame.h"

UTopDownSaveGame::UTopDownSaveGame()
{
	SlotName = "AutoSave";
	UserIndex = 0; // SinglePlayer
}

UTopDownSaveGame* UTopDownSaveGame::CreateSaveGameInstance()
{
	// Create a new, empty SaveGame object to set data on and then pass to SaveGameToSlot.
	return Cast<UTopDownSaveGame>( UGameplayStatics::CreateSaveGameObject( UTopDownSaveGame::StaticClass() ) );
}

void UTopDownSaveGame::Save()
{
	// Save the contents of the SaveGameObject to a slot.
	UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
}

UTopDownSaveGame* UTopDownSaveGame::Load(FString Slot, uint32 Index)
{
	// Save the contents of the SaveGameObject to a slot.
	// SaveGameObject Object containing loaded game state(NULL if load fails)
	return Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, Index));
}
