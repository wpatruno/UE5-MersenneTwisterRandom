// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**	Evaluates how "lucky" a rolled value is based on its probability.
 * Returns a value from 0.0 to 1.0 where:
 * - 0.0 = extremely lucky (very rare outcome)
 * - 1.0 = unlucky (very common outcome)
 * - 0.5 = neutral (average probability)
 */
class MERSENNETWISTERRANDOM_API RandomEvaluate
{
public:

	/**	Evaluates luck based on position in range. Values closer to Max are considered luckier.
	 * @param Value The rolled value to evaluate
	 * @param Min Minimum possible value in the range
	 * @param Max Maximum possible value in the range (considered luckiest)
	 * @return Luck factor: 0.0 = very lucky, 1.0 = unlucky
	 */
	static float EvalFloatMax(const float Value, const float Min = 0.0f, const float Max = 1.0f);

	/**	Evaluates luck based on boolean outcome probability.
	 * @param Value The boolean result that was rolled
	 * @param Probability The probability that Value should be true (0.0 to 1.0)
	 * @return Luck factor: 0.0 = very lucky, 1.0 = unlucky
	 */
	static float EvalBoolTrue(const bool Value, const float Probability = 0.5f);

	/**	Evaluates luck based on generation curve and rarity position.
	 * The curve maps random time (0-1) to generated values.
	 * The rarityTime parameter defines which time position (0-1) produces the rarest/luckiest values.
	 * @param Value The generated value to evaluate (e.g., year 450)
	 * @param Curve Generation curve that maps time (0-1) to values (e.g., years 100-800)
	 * @param RarityTime Time position (0-1) that produces the rarest values (default 0.0)
	 * @return Luck factor: 0.0 = very lucky (close to rarity position), 1.0 = unlucky (far from rarity position)
	 */
	static float EvalCurve(const float Value, const FRichCurve& Curve, const float RarityTime = 0.0f);
	
	/**	Fast version that directly checks value against the rarest possible value.
	 * Simplified version that doesn't analyze the full curve behavior.
	 * @param Value The generated value to evaluate
	 * @param Curve Generation curve that maps time (0-1) to values
	 * @param RarityTime Time position (0-1) that produces the rarest values (default 0.0)
	 * @return Luck factor: 0.0 = very lucky (close to rarity position), 1.0 = unlucky (far from rarity position)
	 */
	static float EvalCurveFast(const float Value, const FRichCurve& Curve, const float RarityTime = 0.0f);
};
