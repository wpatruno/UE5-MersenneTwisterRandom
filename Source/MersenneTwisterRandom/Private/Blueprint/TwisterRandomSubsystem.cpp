// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/TwisterRandomSubsystem.h"

void UTwisterRandomSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Random = RandomEngine(RandomEngine::StaticNewSeed());
}

float UTwisterRandomSubsystem::RandFloat(const float Min, const float Max)
{
	return Random.RandFloat(Min, Max);
}

int32 UTwisterRandomSubsystem::RandInt(const int32 Min, const int32 Max)
{
	return Random.RandInt(Min, Max);
}

bool UTwisterRandomSubsystem::RandBool(const float Probability)
{
	return Random.RandBool(Probability);
}

float UTwisterRandomSubsystem::RandFloatBiased(const float Min, const float Max, const float BiasedToward, const int32 BiasForce)
{
	return Random.RandFloatBiased(Min, Max, BiasedToward, BiasForce);
}

bool UTwisterRandomSubsystem::RandBoolBiased(const float Probability, const bool BiasTowardTrue, const int32 BiasForce)
{
	return Random.RandBoolBiased(Probability, BiasTowardTrue, BiasForce);
}

float UTwisterRandomSubsystem::RandGaussian(const float Mean, const float StdDev)
{
	return Random.RandGaussian(Mean, StdDev);
}

float UTwisterRandomSubsystem::RandGaussianClamped(const float Min, const float Max, const float Bias, const float Spread)
{
	return Random.RandGaussianClamped(Min, Max, Bias, Spread);
}

float UTwisterRandomSubsystem::RandGaussianTruncated(const float Min, const float Max, const float Bias, const float Spread)
{
	return Random.RandGaussianTruncated(Min, Max, Bias, Spread);
}

int32 UTwisterRandomSubsystem::RandWeighted(const TArray<float>& Weights)
{
	return Random.RandWeighted(Weights);
}

int32 UTwisterRandomSubsystem::RollDice(const int32 NumDice, const int32 Sides)
{
	return Random.RollDice(NumDice, Sides);
}

int32 UTwisterRandomSubsystem::RollDiceArray(const TArray<int32>& DiceArray)
{
	return Random.RollDiceArray(DiceArray);
}

int32 UTwisterRandomSubsystem::GetRootSeed() const
{
	return Random.GetRootSeed();
}

void UTwisterRandomSubsystem::RerollSeed()
{
	Random = RandomEngine(RandomEngine::StaticNewSeed());
}

void UTwisterRandomSubsystem::SetSeed(const int32 InSeed)
{
	Random = RandomEngine(InSeed);
}

int32 UTwisterRandomSubsystem::StaticNewSeed()
{
	return RandomEngine::StaticNewSeed();
}

FGuid UTwisterRandomSubsystem::StaticNewGuid()
{
	return RandomEngine::StaticNewGuid();
}

int32 UTwisterRandomSubsystem::StaticRandInt(const int32 Min, const int32 Max)
{
	return RandomEngine::StaticRandInt(Min, Max);
}

float UTwisterRandomSubsystem::StaticRandFloat(const float Min, const float Max)
{
	return RandomEngine::StaticRandFloat(Min, Max);
}

int32 UTwisterRandomSubsystem::StaticRandIntUnreal(const int32 Min, const int32 Max)
{
	return RandomEngine::StaticRandIntUnreal(Min, Max);
}

float UTwisterRandomSubsystem::StaticRandFloatUnreal(const float Min, const float Max)
{
	return RandomEngine::StaticRandFloatUnreal(Min, Max);
}

bool UTwisterRandomSubsystem::StaticRandBoolUnreal(const float Probability)
{
	return RandomEngine::StaticRandBoolUnreal(Probability);
}
