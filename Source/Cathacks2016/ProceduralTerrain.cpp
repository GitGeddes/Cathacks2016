// Fill out your copyright notice in the Description page of Project Settings.

//#include <random>
#include "Cathacks2016.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
#include "PaperTileSet.h"
#include "PerlinNoise.h"
#include "ProceduralTerrain.h"

// Sets default values
AProceduralTerrain::AProceduralTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	map = LoadObject<UPaperTileMap>(NULL, TEXT("/Game/2DSideScrollerCPP/Maps/WorldMap.WorldMap"), NULL, LOAD_None, NULL);
	sheet = LoadObject<UPaperTileMap>(NULL, TEXT("/Game/2DSideScrollerCPP/Maps/TempMap.TempMap"), NULL, LOAD_None, NULL);
}

// Called when the game starts or when spawned
void AProceduralTerrain::BeginPlay()
{
	Super::BeginPlay();

	// Make new PaperTileMapComponent with the texture sheet as the TileMap
	tiles = NewObject<UPaperTileMapComponent>();
	tiles->CreateNewOwnedTileMap();
	tiles->MakeTileMapEditable();
	tiles->SetTileMap(sheet);

	// A few of the 
	FPaperTileInfo air = tiles->GetTile(5, 10, 0);
	FPaperTileInfo grass = tiles->GetTile(5, 0, 0);
	FPaperTileInfo stone = tiles->GetTile(2, 5, 0);

	back = NewObject<UPaperTileLayer>();
	back->ResizeMap(128, 128);

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			double noise = GenerateNoise(i, j);
			if (j < 15 || noise > 0.15 * (j / 8))
			{
				back->SetCell(i, j, air);
			}
			else if (j < 64 || noise > 0.25 * (j / 4))
			{
				back->SetCell(i, j, stone);
			}
			else
			{
				back->SetCell(i, j, stone);
			}
		}
	}

	//this->PostGeneration();

	map->AddExistingLayer(back, 0);
	//front = map->AddNewLayer(1);
}

// Called every frame
void AProceduralTerrain::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called when the game is about to exit
/*FSimpleMulticastDelegate AProceduralTerrain::OnExit()
{
	back->ConditionalBeginDestroy();
	sheet->ConditionalBeginDestroy();
	tiles->ConditionalBeginDestroy();
	map->ConditionalBeginDestroy();
	return FSimpleMulticastDelegate();
}*/

// Helps split up the noise generation code
double AProceduralTerrain::GenerateNoise(int x, int y)
{
	PerlinNoise pn;
	pn.Set(24, 2, 1, 2, rand());
	double noise = pn.GetHeight(x + 1, y + 1) + (1 / 2)*(pn.GetHeight(x * 2 + 1, y * 2 + 1) + (1 / 4)*(pn.GetHeight(x * 4 + 1, y * 4 + 1)));
	return noise;
}

// Fix some errors in the terrain after it's generated
void AProceduralTerrain::PostGeneration()
{
	UPaperTileMap* buff = NewObject<UPaperTileMap>();
	buff->AddExistingLayer(back, 0);

	UPaperTileMapComponent* temp = NewObject<UPaperTileMapComponent>();
	temp->CreateNewOwnedTileMap();
	temp->MakeTileMapEditable();
	temp->SetTileMap(buff);

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			PostGeneration(i, j, temp->GetTile(i, j, 0), temp);
		}
	}

	//buff->ConditionalBeginDestroy();
}

void AProceduralTerrain::PostGeneration(int x, int y, FPaperTileInfo tile, UPaperTileMapComponent* comp)
{
	bool isAirAbove = false;
	if (tile == tiles->GetTile(2, 5, 0) && y > 5) {
		for (int i = 1; i < 5; i++) {
			if (comp->GetTile(x, y + i, 0) != tiles->GetTile(5, 10, 0)) {
				isAirAbove = false;
				i = 5;
			}
			else if (i == 4) {
				isAirAbove = true;
			}
		}
	}
	if (isAirAbove) {
		back->SetCell(x, y, tiles->GetTile(5, 0, 0));
	}

	//comp->ConditionalBeginDestroy();
}