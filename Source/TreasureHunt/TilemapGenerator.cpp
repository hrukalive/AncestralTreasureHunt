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
	
	if (Width <= 16 || Height <= 16)
	{
		return;
	}
	
	FRandomStream Stream(Seed);
	MapWidth = Width;
	MapHeight = Height;

	Tilemap.Reset(MapWidth * MapHeight);
	for (int32 i = 0; i < MapHeight; i++)
	{
		for (int32 j = 0; j < MapWidth; j++)
		{
			Tilemap.Add(0);
			//Tilemap.Add(Stream.FRandRange(0.f, 10.f) < 1.f ? 1 : 0);
		}
	}
	for (int32 i = MapHeight / 2 - 5; i < MapHeight / 2 + 5; i++)
	{
		for (int32 j = MapWidth / 2 - 3; j < MapWidth / 2 + 3; j++)
		{
			Tilemap[i * MapWidth + j] = 1;
		}
	}
	bGenerated = true;
	UE_LOG(LogActor, Warning, TEXT("Tilemap generated"));
}
