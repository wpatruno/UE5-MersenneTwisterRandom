// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RandomEngine.h"

/**
 * 
 */
class MERSENNETWISTERRANDOM_API RandomUtility
{
	/** The RandomEngine instance used for all random generation */
	RandomEngine Engine;

public:
	RandomUtility();

	/**
	 * Constructor - Initializes the random engine with a specific seed
	 * @param InSeed - The seed value for reproducible random generation
	 */
	RandomUtility(int32 InSeed);
	~RandomUtility();

	/**
	 * Gets the current seed used by the random engine
	 * @return The seed value
	 */
	int32 GetSeed() const;

	FColor RandColor();

	FColor RandColorAlpha();

	FVector RandVector(const float Min, const float Max);

	FVector RandVectorNormalized();

	FVector2D RandVector2D(const float Min = -1.0f, const float Max = 1.0f);

	FVector2D RandVector2DNormalized();

	FVector2D RandVector2DInCircle(const float Radius = 1.0f);

	FVector2D RandVector2DOnCircle(const float Radius = 1.0f);

	FVector RandPointInSphere(const float Radius = 1.0f);

	FVector RandPointOnSphere(const float Radius = 1.0f);

	FVector RandPointInCircle(const float Radius = 1.0f);

	FVector RandPointOnCircle(const float Radius = 1.0f);

	FRotator RandRotator();

	FQuat RandQuat();

	template <typename T>
	T RandArrayElement(const TArray<T>& Array);

	template <typename T>
	void ShuffleArray(TArray<T>& Array);

	/**
	 * Returns a random UObject* element from an array
	 * @param Array - The array of UObject* to select from
	 * @return Random UObject* from the array, or nullptr if array is empty
	 */
	UObject* RandArrayElementObject(const TArray<UObject*>& Array);

	/**
	 * Shuffles an array of UObject* in place using Fisher-Yates algorithm
	 * @param Array - The array of UObject* to shuffle
	 */
	void ShuffleArrayObject(TArray<UObject*>& Array);

	float RandCurveValue(const FRuntimeFloatCurve& Curve);

	float RandCurveAsset(const UCurveFloat& Curve);

	float RandCurveRange(const FRuntimeFloatCurve& Curve, const float Min, const float Max);
};
