// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "ProceduralTerrain.generated.h"

using namespace std;

UCLASS()
class CATHACKS2016_API AProceduralTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralTerrain();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called(?) when game is about to exit
	FSimpleMulticastDelegate OnExit();

	// Generate a combination of a gradient, perlin, and white noise,
	//   using x and y values as sample points
	double GenerateNoise(int width, int height);

	// Test for blocks like stone at the top of the world and change them
	void PostGeneration();
	void PostGeneration(int x, int y, FPaperTileInfo tile, UPaperTileMapComponent* comp);

private:
	UPaperTileMap* map;					// Final map
	UPaperTileMap* sheet;				// Copy of the texture sheet in TileMap format
	UPaperTileMapComponent* tiles;		// Parent of sheet, needed to access individual Tiles
	UPaperTileLayer* front;				// Unimplemented, layer extends forward in front of player
	UPaperTileLayer* back;				// Layer with all blocks with collision
};