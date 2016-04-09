// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Cathacks2016.h"
#include "Cathacks2016GameMode.h"
#include "Cathacks2016Character.h"

ACathacks2016GameMode::ACathacks2016GameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ACathacks2016Character::StaticClass();	
}
