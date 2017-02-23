// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCaptnCaps, Log, All);

UENUM(BlueprintType, Blueprintable)
enum class EStencilColor : uint8
{
	SC_Green = 250 UMETA(DisplayName = "Green"),
	SC_Blue = 251 UMETA(DisplayName = "Blue"),
	SC_Red = 252 UMETA(DisplayName = "Red"),
	SC_Orange = 253 UMETA(DisplayName = "Orange"),
};
