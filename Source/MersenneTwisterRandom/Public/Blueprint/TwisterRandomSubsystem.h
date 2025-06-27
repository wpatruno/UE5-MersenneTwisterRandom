// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "System/RandomEngine.h"
#include "TwisterRandomSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MERSENNETWISTERRANDOM_API UTwisterRandomSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

	RandomEngine Random;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Utility", meta = (DisplayName = "Get Root Seed"))
	int32 GetRootSeed() const;

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Utility", meta = (DisplayName = "Reroll Seed"))
	void RerollSeed();

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Utility", meta = (DisplayName = "Set Seed"))
	void SetSeed(const int32 InSeed);

	UFUNCTION(BlueprintCallable, Category = "Twister Random", meta = (DisplayName = "Random Float"))
	float RandFloat(const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random", meta = (DisplayName = "Random Integer"))
	int32 RandInt(const int32 Min = 0, const int32 Max = 1000);

	UFUNCTION(BlueprintCallable, Category = "Twister Random", meta = (DisplayName = "Random Boolean"))
	bool RandBool(const float Probability = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Biased", meta = (DisplayName = "Random Float Biased"))
	float RandFloatBiased(const float Min, const float Max, const float BiasedToward, const int32 BiasForce = 2);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Biased", meta = (DisplayName = "Random Boolean Biased"))
	bool RandBoolBiased(const float Probability = 0.5f, const bool BiasTowardTrue = true, const int32 BiasForce = 3);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Gaussian", meta = (DisplayName = "Random Gaussian"))
	float RandGaussian(const float Mean = 0.0f, const float StdDev = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Gaussian", meta = (DisplayName = "Random Gaussian Clamped"))
	float RandGaussianClamped(const float Min, const float Max, const float Bias = 0.0f, const float Spread = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Gaussian", meta = (DisplayName = "Random Gaussian Truncated"))
	float RandGaussianTruncated(const float Min, const float Max, const float Bias = 0.0f, const float Spread = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Weighted", meta = (DisplayName = "Random Weighted"))
	int32 RandWeighted(const TArray<float>& Weights);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Dice", meta = (DisplayName = "Roll Dice"))
	int32 RollDice(const int32 NumDice, const int32 Sides);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Dice", meta = (DisplayName = "Roll Dice Array"))
	int32 RollDiceArray(const TArray<int32>& DiceArray);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Curve", meta = (DisplayName = "Random Curve Value"))
	float RandCurveValue(const FRuntimeFloatCurve& Curve);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Curve", meta = (DisplayName = "Random Curve Range"))
	float RandCurveRange(const FRuntimeFloatCurve& Curve, const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|State", meta = (DisplayName = "Discard"))
	void Discard(const int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|State", meta = (DisplayName = "Jump To State"))
	void JumpToState(const int32 TargetState);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|State", meta = (DisplayName = "Get Current State"))
	int32 GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category = "Twister Random|State", meta = (DisplayName = "Reset"))
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "Twister Random|State", meta = (DisplayName = "Advance"))
	void Advance(const int32 Steps);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Static", meta = (DisplayName = "Generate New Seed"))
	static int32 StaticNewSeed();

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Static", meta = (DisplayName = "Generate New GUID"))
	static FGuid StaticNewGuid();

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Static", meta = (DisplayName = "Static Random Integer"))
	static int32 StaticRandInt(const int32 Min, const int32 Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Static", meta = (DisplayName = "Static Random Float"))
	static float StaticRandFloat(const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Unreal", meta = (DisplayName = "Unreal Random Integer"))
	static int32 StaticRandIntUnreal(const int32 Min, const int32 Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Unreal", meta = (DisplayName = "Unreal Random Float"))
	static float StaticRandFloatUnreal(const float Min, const float Max);

	UFUNCTION(BlueprintCallable, Category = "Twister Random|Unreal", meta = (DisplayName = "Unreal Random Boolean"))
	static bool StaticRandBoolUnreal(const float Probability = 0.5f);
};
