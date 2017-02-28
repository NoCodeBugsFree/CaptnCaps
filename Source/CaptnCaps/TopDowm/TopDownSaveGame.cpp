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
	return Cast<UTopDownSaveGame>( UGameplayStatics::CreateSaveGameObject( UTopDownSaveGame::StaticClass() ) );
}

void UTopDownSaveGame::Save()
{
	UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
}

UTopDownSaveGame* UTopDownSaveGame::Load(FString Slot, uint32 Index)
{
	return Cast<UTopDownSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, Index));
}
