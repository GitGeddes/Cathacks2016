// Fill out your copyright notice in the Description page of Project Settings.

#include "Cathacks2016.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
#include "PaperTileSet.h"
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

	FPaperTileInfo tile = tiles->GetTile(2, 5, 0);

	back = NewObject<UPaperTileLayer>();
	back->ResizeMap(100, 100);

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			back->SetCell(i, j, tile);
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
	back->ConditionalBeginDestroy();
	front->ConditionalBeginDestroy();
	sheet->ConditionalBeginDestroy();
	tiles->ConditionalBeginDestroy();
	delete map->TileLayers[0];
	delete sheet->TileLayers[0];
	return FSimpleMulticastDelegate();
}