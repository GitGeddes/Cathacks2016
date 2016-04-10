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

	tiles = NewObject<UPaperTileMapComponent>();
	tiles->CreateNewOwnedTileMap();
	tiles->MakeTileMapEditable();
	tiles->SetTileMap(sheet);

	FPaperTileInfo air = tiles->GetTile(5, 10, 0);
	FPaperTileInfo grass = tiles->GetTile(5, 0, 0);
	FPaperTileInfo stone = tiles->GetTile(2, 5, 0);

	back = NewObject<UPaperTileLayer>();
	back->ResizeMap(128, 128);

	PerlinNoise pn;
	pn.Set(5, 10, 1, 2, rand());

	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			double noise = pn.GetHeight(i + 1, j + 1) + (1 / 2)*(pn.GetHeight(i * 2 + 1, j * 2 + 1) + (1 / 4)*(pn.GetHeight(i * 4 + 1, j * 4 + 1)));
			if (j < 50)
			{
				back->SetCell(i, j, air);
			}
			else if (j < 25)
			{
				back->SetCell(i, j, grass);
			}
			else
			{
				back->SetCell(i, j, stone);
			}
		}
	}

	map->AddExistingLayer(back, 0);
	//front = map->AddNewLayer(1);
}

// Called every frame
void AProceduralTerrain::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called when the game is about to exit
FSimpleMulticastDelegate AProceduralTerrain::OnExit()
{
	back->BeginDestroy();
	sheet->BeginDestroy();
	tiles->BeginDestroy();
	map->BeginDestroy();
	return FSimpleMulticastDelegate();
}

// Helps split up the noise generation code
double AProceduralTerrain::GenerateNoise(int width, int height)
{
	return 0.0;
}
