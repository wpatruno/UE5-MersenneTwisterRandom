// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <random>
#include "CoreMinimal.h"

/**
 * RandomEngine - A high-quality random number generator wrapper
 * 
 * This class provides a consistent interface for generating random numbers using
 * the Mersenne Twister (mt19937) algorithm. It maintains state for seeded generation
 * and provides both instance-based and static methods for different use cases.
 * 
 * Features:
 * - Seeded random generation for reproducible results
 * - Roll counting for debugging and analysis
 * - High-quality random number generation
 * - Support for integers, floats, and booleans
 * - Static methods for one-shot generation
 */
class MERSENNETWISTERRANDOM_API RandomEngine
{
	/** The seed used to initialize the random generator */
	int32 Seed;

	/** Mersenne Twister random number generator */
	std::mt19937 Generator;

public:
	RandomEngine();

	/**
	 * Constructor - Initializes the random engine with a specific seed
	 * @param InSeed - The seed value for reproducible random generation
	 */
	RandomEngine(int32 InSeed);

	/**
	 * Destructor
	 */
	~RandomEngine();

	int32 GetRootSeed() const;

	/**
	 * Generates a random integer within the specified range (inclusive)
	 * @param Min - Minimum value (inclusive), defaults to 0
	 * @param Max - Maximum value (inclusive), defaults to 1000
	 * @return Random integer between Min and Max
	 */
	int32 RandInt(const int32 Min = 0, const int32 Max = 1000);

	/**
	 * Generates a random float within the specified range (inclusive)
	 * @param Min - Minimum value (inclusive), defaults to 0.0f
	 * @param Max - Maximum value (inclusive), defaults to 1.0f
	 * @return Random float between Min and Max
	 */
	float RandFloat(const float Min = 0.0f, const float Max = 1.0f);

	/**
	 * Generates a random float with bias toward a specific value
	 * Uses multiple samples and selects the one closest to bias point
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @param BiasedToward - Value to bias toward (should be between Min and Max)
	 * @param BiasForce - Strength of bias (1 = no bias, higher values = stronger bias)
	 * @return Random float between Min and Max with bias toward BiasedToward
	 */
	float RandFloatBiased(const float Min, const float Max, const float BiasedToward, const int32 BiasForce = 2);

	/**
	 * Generates a random boolean value (true/false) with specified probability
	 * @param Probability - Probability of returning true (0.0 = never, 1.0 = always, 0.5 = 50/50)
	 * @return Random boolean value based on probability
	 */
	bool RandBool(const float Probability = 0.5f);

	/**
	 * Generates a biased boolean value with higher probability toward preferred outcome
	 * Uses RandFloatBiased to create consistent bias behavior across random functions
	 * @param Probability - Base probability of returning true (0.0 to 1.0)
	 * @param BiasTowardTrue - Whether to bias toward true or false
	 * @param BiasForce - Strength of bias (1 = no bias, higher values = stronger bias toward preferred outcome)
	 * @return Biased boolean value
	 */
	bool RandBoolBiased(const float Probability = 0.5f, const bool BiasTowardTrue = true, const int32 BiasForce = 3);

	/**
	 * Generates a random float using Gaussian (normal) distribution
	 * Creates a bell curve with most values near the mean
	 * @param Mean - Center of the distribution
	 * @param StdDev - Standard deviation (spread) of the distribution
	 * @return Random float from Gaussian distribution
	 */
	float RandGaussian(const float Mean = 0.0f, const float StdDev = 1.0f);

	/**
	 * Generates a random float using Gaussian distribution clamped to a range
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @param Bias - Value to bias toward (center of bell curve)
	 * @param Spread - How spread out the values are (lower = more concentrated)
	 * @return Random float between Min and Max with Gaussian distribution
	 */
	float RandGaussianClamped(const float Min, const float Max, const float Bias = 0.0f, const float Spread = 1.0f);

	/**
	 * Generates a random index based on weighted probabilities
	 * @param Weights - Array of weights (higher values = higher probability)
	 * @return Random index from 0 to Weights.Num()-1, or -1 if invalid input
	 */
	int32 RandWeighted(const TArray<float>& Weights);

	/**
	 * Rolls multiple dice and returns the sum
	 * @param NumDice - Number of dice to roll
	 * @param Sides - Number of sides on each die
	 * @return Sum of all dice rolls, or 0 if invalid input
	 */
	int32 RollDice(const int32 NumDice, const int32 Sides);

	/* STATIC METHODS */

	/**
	 * Generates a new random seed using hardware entropy
	 * @return A new random seed value
	 */
	static int32 StaticNewSeed();

	/**
	 * Generates a random integer using Unreal's built-in random generator (lower quality)
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @return Random integer between Min and Max
	 */
	static int32 StaticRandIntUnreal(const int32 Min, const int32 Max);

	/**
	 * Generates a random float using Unreal's built-in random generator (lower quality)
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @return Random float between Min and Max
	 */
	static float StaticRandFloatUnreal(const float Min, const float Max);

	/**
	 * Generates a random boolean using Unreal's built-in random generator (lower quality)
	 * @param Probability - Probability of returning true (0.0 = never, 1.0 = always, 0.5 = 50/50)
	 * @return Random boolean value based on probability
	 */
	static bool StaticRandBoolUnreal(const float Probability = 0.5f);

	/**
	 * Generates a random integer using a new high-quality generator instance
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @return Random integer between Min and Max
	 */
	static int32 StaticRandInt(const int32 Min, const int32 Max);

	/**
	 * Generates a random float using a new high-quality generator instance
	 * @param Min - Minimum value (inclusive)
	 * @param Max - Maximum value (inclusive)
	 * @return Random float between Min and Max
	 */
	static float StaticRandFloat(const float Min, const float Max);

	/**
	 * Generates a new GUID using high-quality random number generation
	 * @return A new randomly generated GUID
	 */
	static FGuid StaticNewGuid();
};
