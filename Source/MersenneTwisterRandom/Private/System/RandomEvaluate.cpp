// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RandomEvaluate.h"

float RandomEvaluate::EvalFloatMax(const float Value, const float Min, const float Max)
{
	// Normalize the range to [0, 1]
	const float Range = Max - Min;
	if (Range <= 0.0f)
	{
		return 1.0f; // Invalid range
	}

	// Calculate where in the range the value falls (0 = min, 1 = max)
	const float NormalizedValue = (Value - Min) / Range;
	
	// Return the probability of getting this value or higher
	// For uniform distribution, this is just 1 - normalized value
	// Lower return value = luckier roll (closer to max)
	return 1.0f - NormalizedValue;
}

float RandomEvaluate::EvalBoolTrue(const bool Value, const float Probability)
{
	// Clamp probability to valid range [0.0, 1.0]
	const float ClampedProbability = FMath::Clamp(Probability, 0.0f, 1.0f);

	// If Value is true, return the probability (higher probability = less lucky)
	// If Value is false, return 1 - probability (lower probability = less lucky)
	if (Value)
	{
		// True result: probability represents how expected this result was
		return ClampedProbability;
	}
	else
	{
		// False result: (1-probability) represents how expected this result was
		return 1.0f - ClampedProbability;
	}
}

float RandomEvaluate::EvalCurve(const float Value, const FRichCurve& Curve, const float RarityTime)
{
	if (Curve.IsEmpty())
	{
		return 0.5f; // Neutral luck for empty curve
	}

	// Clamp RarityTime to valid range [0, 1]
	const float ClampedRarityTime = FMath::Clamp(RarityTime, 0.0f, 1.0f);

	// Get the curve's time range (should be 0-1 but we handle any range)
	const float MinTime = Curve.GetFirstKey().Time;
	const float MaxTime = Curve.GetLastKey().Time;
	const float TimeRange = MaxTime - MinTime;
	
	if (TimeRange <= 0.0f)
	{
		return 0.5f; // Neutral luck for invalid time range
	}

	// Convert RarityTime to actual curve time
	const float ActualRarityTime = MinTime + (ClampedRarityTime * TimeRange);
	
	// Get the rarest value (the value at the rarity time position)
	const float RarestValue = Curve.Eval(ActualRarityTime);

	// Find the full range of possible values from the curve
	float MinValue = Curve.Eval(MinTime);
	float MaxValue = Curve.Eval(MaxTime);
	
	// Sample the curve to find actual min/max values
	const int32 SampleCount = 100;
	for (int32 i = 0; i < SampleCount; ++i)
	{
		const float SampleTime = MinTime + (i * TimeRange / static_cast<float>(SampleCount - 1));
		const float SampleValue = Curve.Eval(SampleTime);
		MinValue = FMath::Min(MinValue, SampleValue);
		MaxValue = FMath::Max(MaxValue, SampleValue);
	}

	const float ValueRange = MaxValue - MinValue;
	if (ValueRange <= SMALL_NUMBER)
	{
		return 0.5f; // Neutral luck for constant curve
	}

	// Calculate how far the actual value is from the rarest value
	const float DistanceFromRarest = FMath::Abs(Value - RarestValue);
	
	// Calculate the maximum possible distance from the rarest value
	const float MaxDistanceFromRarest = FMath::Max(
		FMath::Abs(MinValue - RarestValue),
		FMath::Abs(MaxValue - RarestValue)
	);

	if (MaxDistanceFromRarest <= SMALL_NUMBER)
	{
		return 0.5f; // Neutral luck if rarest value is at the middle
	}

	// Calculate luck: closer to rarest value = luckier (lower return value)
	const float DistanceRatio = DistanceFromRarest / MaxDistanceFromRarest;
	
	// Apply a curve to make the luck feel more natural
	// Values very close to the rarest are extremely lucky
	const float LuckFactor = FMath::Pow(DistanceRatio, 0.5f); // Square root for more gradual falloff
	
	return FMath::Clamp(LuckFactor, 0.0f, 1.0f);
}

float RandomEvaluate::EvalCurveFast(const float Value, const FRichCurve& Curve, const float RarityTime)
{
	// Handle empty curve
	if (Curve.IsEmpty())
	{
		return 0.5f; // Neutral luck for empty curve
	}

	// Clamp RarityTime to valid range [0, 1]
	const float ClampedRarityTime = FMath::Clamp(RarityTime, 0.0f, 1.0f);

	// Get the curve's time range
	const float MinTime = Curve.GetFirstKey().Time;
	const float MaxTime = Curve.GetLastKey().Time;
	const float TimeRange = MaxTime - MinTime;
	
	if (TimeRange <= SMALL_NUMBER)
	{
		return 0.5f; // Neutral luck for invalid time range
	}

	// Convert RarityTime to actual curve time
	const float ActualRarityTime = MinTime + (ClampedRarityTime * TimeRange);
	
	// Get the rarest value (the value at the rarity time position)
	const float RarestValue = Curve.Eval(ActualRarityTime);
	
	// Get the min/max values directly from endpoints (simplified)
	const float MinValue = Curve.Eval(MinTime);
	const float MaxValue = Curve.Eval(MaxTime);
	
	// Use the wider of the two ranges to determine max distance
	const float ValueRange = FMath::Abs(MaxValue - MinValue);
	if (ValueRange <= SMALL_NUMBER)
	{
		return 0.5f; // Neutral luck for constant curve
	}
	
	// Calculate how far the actual value is from the rarest value
	const float DistanceFromRarest = FMath::Abs(Value - RarestValue);
	
	// Simplified max distance calculation - just use the full range
	const float MaxDistanceFromRarest = ValueRange;
	
	// Direct linear mapping of distance to luck
	const float LuckFactor = DistanceFromRarest / MaxDistanceFromRarest;
	
	return FMath::Clamp(LuckFactor, 0.0f, 1.0f);
}
