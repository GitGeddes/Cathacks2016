// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
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

	FSimpleMulticastDelegate OnExit();

private:
	UPaperTileMap* map;
	UPaperTileMapComponent* tiles;
	//UPaperTileSet* tiles;
	UPaperTileLayer* front;
	UPaperTileLayer* back;
	int width;
	int height;
};