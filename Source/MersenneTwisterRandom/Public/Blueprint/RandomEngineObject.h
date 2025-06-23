// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/RandomEngine.h"
#include "UObject/Object.h"
#include "RandomEngineObject.generated.h"

/**
 * Random Engine Object that can be initialized with a seed for reproducible random number generation
 */
UCLASS(BlueprintType, Blueprintable)
class MERSENNETWISTERRANDOM_API URandomEngineObject : public UObject
{
	GENERATED_BODY()

protected:
	RandomEngine Engine;

public:
	// Constructor that takes a seed
	URandomEngineObject();

	// Static factory function to create and initialize with seed (Blueprint-friendly)
	UFUNCTION(BlueprintCallable, Category = "Random Engine", meta = (DisplayName = "Create Random Engine Object"))
	static URandomEngineObject* CreateRandomEngineObject(UObject* Outer, int32 Seed = 0);

	// Initialize with seed
	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	void InitializeWithSeed(int32 InSeed);

	// Get the current seed
	UFUNCTION(BlueprintPure, Category = "Random Engine")
	int32 GetRootSeed() const { return Engine.GetRootSeed(); }

	UFUNCTION(BlueprintPure, Category = "Random Engine")
	float GetFloatPercentage();

	UFUNCTION(BlueprintPure, Category = "Random Engine")
	float GetFloatPercentage01();

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	float GetFloat(const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	float GetFloatBiased(const float Min, const float Max, const float BiasToward, const int32 BiasForce);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	float GetFloatGaussian(const float Mean, const float StandardDeviation);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	float GetFloatGaussianClamped(const float Min, const float Max, const float Mean, const float StandardDeviation);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	int32 GetInteger(const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	bool GetBool(const float Probability01);

	UFUNCTION(BlueprintCallable, Category = "Random Engine")
	UObject* GetRandomSelection(const TArray<UObject*>& ObjectArray);
};
