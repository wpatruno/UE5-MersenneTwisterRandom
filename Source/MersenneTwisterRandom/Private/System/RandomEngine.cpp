// Fill out your copyright notice in the Description page of Project Settings.

#include "System/RandomEngine.h"

RandomEngine::RandomEngine(): RandomEngine(StaticNewSeed())
{
}

/**
 * Constructor - Initializes the random engine with a specific seed
 * @param InSeed - The seed value for reproducible random generation
 */
RandomEngine::RandomEngine(int32 InSeed):
	Seed(InSeed), Generator(InSeed), GeneratedCount(0)
{
}

/**
 * Destructor
 */
RandomEngine::~RandomEngine()
{
}

int32 RandomEngine::GetRootSeed() const
{
	return Seed;
}

/**
 * Generates a random integer within the specified range (inclusive)
 * @param Min - Minimum value (inclusive), defaults to 0
 * @param Max - Maximum value (inclusive), defaults to 1000
 * @return Random integer between Min and Max
 */
int32 RandomEngine::RandInt(const int32 Min, const int32 Max)
{
	std::uniform_int_distribution<int32> Distribution(Min, Max); // Inclusive range
	GeneratedCount++;
	return Distribution(Generator);
}

/**
 * Generates a random float within the specified range (inclusive)
 * @param Min - Minimum value (inclusive), defaults to 0.0f
 * @param Max - Maximum value (inclusive), defaults to 1.0f
 * @return Random float between Min and Max
 */
float RandomEngine::RandFloat(const float Min, const float Max)
{
	std::uniform_real_distribution<float> Distribution(Min, Max); // Inclusive range
	GeneratedCount++;
	return Distribution(Generator);
}

/**
 * Generates a random float with bias toward a specific value
 * Uses multiple samples and selects the one closest to bias point
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @param BiasedToward - Value to bias toward (should be between Min and Max)
 * @param BiasForce - Strength of bias (1 = no bias, higher values = stronger bias)
 * @return Random float between Min and Max with bias toward BiasedToward
 */
float RandomEngine::RandFloatBiased(const float Min, const float Max, const float BiasedToward, const int32 BiasForce)
{
	// Clamp the bias value to be within the range
	const float ClampedBias = FMath::Clamp(BiasedToward, Min, Max);

	// Ensure bias force is at least 1 to avoid division by zero or negative values
	const int32 ClampedBiasForce = FMath::Max(1, BiasForce);

	// If bias force is 1, return regular random float (no bias)
	if (ClampedBiasForce == 1)
	{
		std::uniform_real_distribution<float> Distribution(Min, Max);
		GeneratedCount++;
		return Distribution(Generator);
	}

	// Generate multiple random numbers and select the one closest to bias
	std::uniform_real_distribution<float> Distribution(Min, Max);
	float BestValue = Distribution(Generator);
	GeneratedCount++;
	float BestDistance = FMath::Abs(BestValue - ClampedBias);

	// Generate additional samples based on bias force
	for (int32 i = 1; i < ClampedBiasForce; ++i)
	{
		const float CurrentValue = Distribution(Generator);
		GeneratedCount++;
		const float CurrentDistance = FMath::Abs(CurrentValue - ClampedBias);

		// Keep the value closer to the bias point
		if (CurrentDistance < BestDistance)
		{
			BestValue = CurrentValue;
			BestDistance = CurrentDistance;
		}
	}

	return BestValue;
}

/**
 * Generates a random boolean value (true/false) with specified probability
 * @param Probability - Probability of returning true (0.0 = never, 1.0 = always, 0.5 = 50/50)
 * @return Random boolean value based on probability
 */
bool RandomEngine::RandBool(const float Probability)
{
	// Clamp probability to valid range [0.0, 1.0]
	const float ClampedProbability = FMath::Clamp(Probability, 0.0f, 1.0f);

	// Generate random float and compare against probability threshold
	std::uniform_real_distribution<float> Distribution(0.0f, 1.0f);
	GeneratedCount++;
	return Distribution(Generator) < ClampedProbability;
}

/**
 * Generates a biased boolean value with higher probability toward preferred outcome
 * Uses RandFloatBiased to create consistent bias behavior across random functions
 * @param Probability - Base probability of returning true (0.0 to 1.0)
 * @param BiasTowardTrue - Whether to bias toward true or false
 * @param BiasForce - Strength of bias (1 = no bias, higher values = stronger bias toward preferred outcome)
 * @return Biased boolean value
 */
bool RandomEngine::RandBoolBiased(const float Probability, const bool BiasTowardTrue, const int32 BiasForce)
{
	// Clamp inputs to valid ranges
	const float ClampedProbability = FMath::Clamp(Probability, 0.0f, 1.0f);
	const int32 ClampedBiasForce = FMath::Max(1, BiasForce);

	// If bias force is 1, return regular random bool (no bias)
	if (ClampedBiasForce == 1)
	{
		return RandBool(ClampedProbability);
	}

	// Use RandFloatBiased to generate a biased float, then convert to boolean
	// The bias target depends on whether we want to bias toward true or false
	float BiasTarget;
	if (BiasTowardTrue)
	{
		// Bias toward values that would result in true (< Probability)
		// Target should be halfway between 0 and Probability
		BiasTarget = ClampedProbability * 0.5f;
	}
	else
	{
		// Bias toward values that would result in false (>= Probability)
		// Target should be halfway between Probability and 1.0
		BiasTarget = ClampedProbability + (1.0f - ClampedProbability) * 0.5f;
	}

	// Generate biased float in [0, 1] range and compare to probability threshold
	const float BiasedValue = RandFloatBiased(0.0f, 1.0f, BiasTarget, ClampedBiasForce);
	return BiasedValue < ClampedProbability;
}

/**
 * Generates a new random seed using hardware entropy
 * @return A new random seed value
 */
int32 RandomEngine::StaticNewSeed()
{
	std::random_device Rd; // Uses hardware entropy for seeding
	return Rd();
}

/**
 * Generates a random integer using Unreal's built-in random generator (lower quality)
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @return Random integer between Min and Max
 */
int32 RandomEngine::StaticRandIntUnreal(const int32 Min, const int32 Max)
{
	return FMath::RandRange(Min, Max);
}

/**
 * Generates a random float using Unreal's built-in random generator (lower quality)
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @return Random float between Min and Max
 */
float RandomEngine::StaticRandFloatUnreal(const float Min, const float Max)
{
	return FMath::RandRange(Min, Max);
}

/**
 * Generates a random boolean using Unreal's built-in random generator (lower quality)
 * @param Probability - Probability of returning true (0.0 = never, 1.0 = always, 0.5 = 50/50)
 * @return Random boolean value based on probability
 */
bool RandomEngine::StaticRandBoolUnreal(const float Probability)
{
	// Clamp probability to valid range [0.0, 1.0]
	const float ClampedProbability = FMath::Clamp(Probability, 0.0f, 1.0f);

	// Use Unreal's built-in random float generator and compare against probability threshold
	return FMath::RandRange(0.0f, 1.0f) < ClampedProbability;
}

/**
 * Generates a random integer using a new high-quality generator instance
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @return Random integer between Min and Max
 */
int32 RandomEngine::StaticRandInt(const int32 Min, const int32 Max)
{
	std::mt19937 LocalGenerator(StaticNewSeed());
	std::uniform_int_distribution<int32> Distribution(Min, Max); // Inclusive range
	return Distribution(LocalGenerator);
}

/**
 * Generates a random float using a new high-quality generator instance
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @return Random float between Min and Max
 */
float RandomEngine::StaticRandFloat(const float Min, const float Max)
{
	std::mt19937 LocalGenerator(StaticNewSeed());
	std::uniform_real_distribution<float> Distribution(Min, Max); // Inclusive range
	return Distribution(LocalGenerator);
}

/**
 * Bell curve distribution (most values near center)
 * @param Mean - Mean of the distribution
 * @param StdDev - Standard deviation of the distribution
 * @return Random float from the distribution
 */
float RandomEngine::RandGaussian(const float Mean, const float StdDev)
{
	std::normal_distribution<float> Distribution(Mean, StdDev);
	GeneratedCount++;
	return Distribution(Generator);
}

/**
 * Generates a random float using Gaussian distribution clamped to a range
 * @param Min - Minimum value (inclusive)
 * @param Max - Maximum value (inclusive)
 * @param Bias - Value to bias toward (center of bell curve)
 * @param Spread - How spread out the values are (lower = more concentrated)
 * @param Attempts - How many attempts to make before clamping
 * @return Random float between Min and Max with Gaussian distribution
 */
float RandomEngine::RandGaussianClamped(const float Min, const float Max, const float Bias, const float Spread, const int32 Attempts)
{
	// Clamp bias to be within the range
	const float ClampedBias = FMath::Clamp(Bias, Min, Max);

	// Calculate standard deviation based on range and spread
	// Spread of 1.0 means about 99.7% of values will be within the range
	const float Range = Max - Min;
	const float StdDev = (Range * Spread) / 6.0f; // 6 sigma covers 99.7% of normal distribution

	// Generate Gaussian value and clamp to range
	float Value = 0;
	const int32 MaxAttempts = FMath::Max(Attempts, 1);

	for (int i = 0; i < MaxAttempts; ++i)
	{
		Value = RandGaussian(ClampedBias, StdDev);
		if (Value >= Min && Value <= Max)
		{
			return Value;
		}
	}

	return FMath::Clamp(Value, Min, Max);
}

float RandomEngine::RandGaussianTruncated(const float Min, const float Max, const float Bias, const float Spread)
{
	// Clamp bias to be within the range
	const float ClampedBias = FMath::Clamp(Bias, Min, Max);

	// Calculate standard deviation based on range and spread
	// Spread of 1.0 means about 99.7% of values will be within the range
	const float Range = Max - Min;
	const float StdDev = (Range * Spread) / 6.0f; // 6 sigma covers 99.7% of normal distribution

	for (int i = 0; i < 5; ++i)
	{
		const float Value = RandGaussian(ClampedBias, StdDev);
		if (Value >= Min && Value <= Max)
		{
			return Value;
		}
	}
	return RandFloat(Min, Max);
}

/**
 * Generates a random index based on weighted probabilities
 * @param Weights - Array of weights (higher values = higher probability)
 * @return Random index from 0 to Weights.Num()-1, or -1 if invalid input
 */
int32 RandomEngine::RandWeighted(const TArray<float>& Weights)
{
	// Return -1 for empty array
	if (Weights.Num() == 0)
	{
		return -1;
	}

	// Calculate total weight
	float TotalWeight = 0.0f;
	for (const float Weight : Weights)
	{
		// Only add positive weights
		if (Weight > 0.0f)
		{
			TotalWeight += Weight;
		}
	}

	// Return -1 if no valid weights
	if (TotalWeight <= 0.0f)
	{
		return -1;
	}

	// Generate random value between 0 and total weight
	const float RandomValue = RandFloat(0.0f, TotalWeight);

	// Find which weight range the random value falls into
	float CurrentWeight = 0.0f;
	for (int32 i = 0; i < Weights.Num(); ++i)
	{
		if (Weights[i] > 0.0f)
		{
			CurrentWeight += Weights[i];
			if (RandomValue <= CurrentWeight)
			{
				return i;
			}
		}
	}

	// Fallback (should not reach here with valid input)
	return Weights.Num() - 1;
}

/**
 * Rolls multiple dice and returns the sum
 * @param NumDice - Number of dice to roll
 * @param Sides - Number of sides on each die
 * @return Sum of all dice rolls, or 0 if invalid input
 */
int32 RandomEngine::RollDice(const int32 NumDice, const int32 Sides = 6)
{
	// Validate input
	if (NumDice <= 0 || Sides <= 0)
	{
		return 0;
	}

	// Roll dice and sum the results
	int32 Total = 0;
	for (int32 i = 0; i < NumDice; ++i)
	{
		Total += RandInt(1, Sides);
	}

	return Total;
}

int32 RandomEngine::RollDiceArray(const TArray<int32>& DiceArray)
{
	if (DiceArray.IsEmpty())
	{
		return 0;
	}
	int32 Total = 0;
	for (auto Sides : DiceArray)
	{
		if (Sides >= 1)
		{
			Total += RandInt(1, Sides);
		}
	}
	return Total;
}

float RandomEngine::RandCurveValue(const FRichCurve& Curve)
{
	if (!Curve.IsEmpty())
	{
		const float MinTime = Curve.GetFirstKey().Time;
		const float MaxTime = Curve.GetLastKey().Time;

		const float Result = Curve.Eval(RandFloat(MinTime, MaxTime));
		return Result;
	}
	return 0;
}

float RandomEngine::RandCurveRange(const FRichCurve& Curve, const float Min, const float Max)
{
	if (!Curve.IsEmpty())
	{
		const float Result = Curve.Eval(RandFloat(Min, Max));
		return Result;
	}
	return 0;
}

/**
 * Discards the next N random numbers from the generator
 * Useful for synchronizing multiple generators or skipping ahead
 * @param Count - Number of random values to discard
 */
void RandomEngine::Discard(const uint32 Count)
{
	// Use the discard method of the underlying Mersenne Twister generator
	Generator.discard(Count);
	GeneratedCount += Count;
}

/**
 * Discards random numbers until reaching a specific state
 * @param TargetState - The target state to jump to
 */
void RandomEngine::JumpToState(const uint32 TargetState)
{
	// If we're already at the target state, do nothing
	if (GeneratedCount == TargetState)
	{
		return;
	}
	
	// If target state is ahead of current state, advance
	if (TargetState > GeneratedCount)
	{
		Advance(TargetState - GeneratedCount);
	}
	else
	{
		// If target state is behind current state, reset and advance
		Reset();
		Advance(TargetState);
	}
}

/**
 * Gets the current state of the generator
 * @return Current state value
 */
uint32 RandomEngine::GetCurrentState() const
{
	return GeneratedCount;
}

/**
 * Resets the generator to its initial state with the original seed
 */
void RandomEngine::Reset()
{
	// Reinitialize the generator with the original seed
	Generator = std::mt19937(Seed);
	GeneratedCount = 0;
}

/**
 * Advances the generator by a specific number of steps
 * @param Steps - Number of steps to advance
 */
void RandomEngine::Advance(const uint32 Steps)
{
	Generator.discard(Steps);
	GeneratedCount += Steps;
}

/**
 * Generates a new GUID using high-quality random number generation
 * @return A new randomly generated GUID
 */
FGuid RandomEngine::StaticNewGuid()
{
	std::mt19937 LocalGenerator(StaticNewSeed());
	std::uniform_int_distribution<uint32> Distribution(0, UINT32_MAX);

	// Generate four 32-bit random values to construct the GUID
	const uint32 A = Distribution(LocalGenerator);
	const uint32 B = Distribution(LocalGenerator);
	const uint32 C = Distribution(LocalGenerator);
	const uint32 D = Distribution(LocalGenerator);
	return FGuid(A, B, C, D);
}
