// Fill out your copyright notice in the Description page of Project Settings.


#include "TilemapGenerator.h"

// Sets default values
ATilemapGenerator::ATilemapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tilemap.Reset();
	MapWidth = 0;
	MapHeight = 0;
	bGenerated = false;
}

// Called when the game starts or when spawned
void ATilemapGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATilemapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATilemapGenerator::GenerateTilemap(int32 Seed, int Width, int Height)
{
	bGenerated = false;
	
	auto boxes = engine.randBox(42, 100, 0.9, false, 1, 4, 4, false, 8, 12, 3, 0.65);
	boxes = engine.separateBox(boxes);
	boxes = engine.centerAndCropBox(boxes, Width, Height);
	auto ret = engine.randSelect(boxes, 12, false);
	boxes = ret.first;
	auto rooms = ret.second;
	auto edges = engine.triangulate(rooms);
	auto mst_edges = engine.mst(edges, 12);
	mst_edges = engine.addSomeEdgesBack(42, edges, mst_edges, 0.1);
	auto lines = engine.lineConnect(42, rooms, mst_edges, 3, false, 0.5);
	auto ret2 = engine.selectCorridors(boxes, lines, 12);
	boxes = ret2.first;
	auto corridors = ret.second;
	auto tiles = engine.tiling(rooms, corridors, lines, Width, Height);

	Tilemap.Reset();
	for (int v : tiles)
		Tilemap.Add(v);

	bGenerated = true;
	MapWidth = Width;
	MapHeight = Height;
	UE_LOG(LogActor, Warning, TEXT("Tilemap generated"));

    FString tileStr;
    tileStr += "------------\n";
	for (int32 i = 0; i < MapHeight; i++)
	{
		for (int32 j = 0; j < MapWidth; j++)
		{
			if (Tilemap[i * MapWidth + j] == 0)
				tileStr += ".";
			else
				tileStr += FString::FromInt(Tilemap[i * MapWidth + j]);
		}
		tileStr += "\n";
	}
    UE_LOG(LogActor, Warning, TEXT("%s"), *tileStr);
}
