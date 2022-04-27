// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
			UPARAM(DisplayName = "Estimated Width") int Width,
			UPARAM(DisplayName = "Estimated Height") int Height);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<int> Tilemap;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MapWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int MapHeight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bGenerated;
};
