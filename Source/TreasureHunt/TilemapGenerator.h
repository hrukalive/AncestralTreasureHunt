// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerationEngine.h"
#include "TilemapGenerator.generated.h"

UCLASS(Blueprintable)
class TREASUREHUNT_API ATilemapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATilemapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void GenerateTilemap(
			UPARAM(DisplayName = "Seed") int32 Seed,
			UPARAM(DisplayName = "Map Width") int Width = 64,
			UPARAM(DisplayName = "Map Height") int Height = 64,
			UPARAM(DisplayName = "Num Rand Boxes") int NumBox = 100,
			UPARAM(DisplayName = "Small Box Probability") float SmallBoxProb = 0.9f,
			UPARAM(DisplayName = "Small Box Ratio Limit") float SmallBoxRatioLimit = 4.0f,
			UPARAM(DisplayName = "Large Box Ratio Limit") float LargeBoxRatioLimit = 3.0f,
			UPARAM(DisplayName = "Large Box Radius Mul") float LargeBoxRadiusMultiplier = 0.65f,
			UPARAM(DisplayName = "Small Box Use Gaussian") bool SmallBoxUseNormalDist = false,
			UPARAM(DisplayName = "Small Box UnifA or Mu") float SmallBoxParamA = 1.0f,
			UPARAM(DisplayName = "Small Box UnifB or Sigma") float SmallBoxParamB = 4.0f,
			UPARAM(DisplayName = "Large Box Use Gaussian") bool LargeBoxUseNormalDist = false,
			UPARAM(DisplayName = "Large Box UnifA or Mu") float LargeBoxParamA = 8.0f,
			UPARAM(DisplayName = "Large Box UnifB or Sigma") float LargeBoxParamB = 12.0f,
			UPARAM(DisplayName = "Num Main Rooms") int NumRooms = 12,
			UPARAM(DisplayName = "Allow Main Rooms Touching") bool AllowTouching = false ,
			UPARAM(DisplayName = "Edge Add Back Probability") float AddBackProb = 0.1f,
			UPARAM(DisplayName = "Direct Connect Padding") int OverlapPadding = 3,
			UPARAM(DisplayName = "Add Both Direct Connection") bool AddBothDirection = false,
			UPARAM(DisplayName = "Direct Connect Horizontal First Probability") float FirstHorizontalProb = 0.5f,
			UPARAM(DisplayName = "Max Aux Room Size") int MaxRoomSize = 12
		);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int> Tilemap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MapWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MapHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bGenerated;
	
private:
	DungeonGenerationEngine engine;
};
