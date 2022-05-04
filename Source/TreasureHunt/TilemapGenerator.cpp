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

void ATilemapGenerator::GenerateTilemap(
	int32 Seed, int Width, int Height, bool UseRectRegion, float RadiusX, float RadiusY,
	int NumBox, int MaxIteration, float SmallBoxProb, float SmallBoxRatioLimit, float LargeBoxRatioLimit,
	float LargeBoxRadiusMultiplier, bool SmallBoxUseNormalDist, float SmallBoxParamA, float SmallBoxParamB,
	bool LargeBoxUseNormalDist, float LargeBoxParamA, float LargeBoxParamB,
	int NumRooms, bool AllowTouching, float AddBackProb, int OverlapPadding,
	bool AddBothDirection, float FirstHorizontalProb, int MaxRoomSize
)
{
	bGenerated = false;
	
	if (Width < 0 || Height < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid map size"));
		return;
	}
	auto boxes = engine.randBox(
		Seed, UseRectRegion, RadiusX, RadiusY,
		NumBox, MaxIteration, SmallBoxProb, SmallBoxUseNormalDist, SmallBoxParamA, SmallBoxParamB, SmallBoxRatioLimit,
		LargeBoxUseNormalDist, LargeBoxParamA, LargeBoxParamB, LargeBoxRatioLimit, LargeBoxRadiusMultiplier
	);
	boxes = engine.separateBox(boxes);
	if (boxes.size() == 0)
		return;
	boxes = engine.centerAndCropBox(boxes, Width, Height);
	if (boxes.size() == 0)
		return;
	auto ret = engine.randSelect(boxes, NumRooms, AllowTouching);
	boxes = ret.first;
	DungeonGenerationEngine::RoomBoxVec rooms = ret.second;
	if (rooms.size() == 0)
		return;
	auto edges = engine.triangulate(rooms);
	if (edges.size() == 0)
		return;
	auto mst_edges = engine.mst(edges);
	if (mst_edges.size() == 0)
		return;
	mst_edges = engine.addSomeEdgesBack(Seed, edges, mst_edges, AddBackProb);
	auto lines = engine.lineConnect(Seed, rooms, mst_edges, OverlapPadding, AddBothDirection, FirstHorizontalProb);
	auto ret2 = engine.selectCorridors(boxes, lines, MaxRoomSize);
	boxes = ret2.first;
	DungeonGenerationEngine::RoomBoxVec corridors = ret.second;
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
