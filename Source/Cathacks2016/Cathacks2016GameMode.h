// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "Cathacks2016GameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of Cathacks2016Character

UCLASS(minimalapi)
class ACathacks2016GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ACathacks2016GameMode();
};
