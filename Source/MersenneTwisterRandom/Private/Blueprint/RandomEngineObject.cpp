// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/RandomEngineObject.h"

URandomEngineObject::URandomEngineObject()
{
	// Initialize with a default seed of 0
}

URandomEngineObject* URandomEngineObject::CreateRandomEngineObject(UObject* Outer, int32 Seed)
{
	// Create the object
	URandomEngineObject* NewRandomEngine = NewObject<URandomEngineObject>(Outer);

	// Initialize with the provided seed
	if (NewRandomEngine)
	{
		NewRandomEngine->InitializeWithSeed(Seed);
	}

	return NewRandomEngine;
}

void URandomEngineObject::InitializeWithSeed(int32 InSeed)
{
	if (InSeed == 0)
	{
		InSeed = RandomEngine::StaticNewSeed();
	}
	Engine = RandomEngine(InSeed);
}

float URandomEngineObject::GetFloatPercentage()
{
	return Engine.RandFloat(0, 100);
}

float URandomEngineObject::GetFloatPercentage01()
{
	return Engine.RandFloat(0, 1);
}

float URandomEngineObject::GetFloat(const float Min, const float Max)
{
	return Engine.RandFloat(Min, Max);
}

float URandomEngineObject::GetFloatBiased(const float Min, const float Max, const float BiasToward, const int32 BiasForce = 2)
{
	return Engine.RandFloatBiased(Min, Max, BiasToward, BiasForce);
}

float URandomEngineObject::GetFloatGaussian(const float Mean, const float StandardDeviation)
{
	return Engine.RandGaussian(Mean, StandardDeviation);
}

float URandomEngineObject::GetFloatGaussianClamped(const float Min, const float Max, const float Mean, const float StandardDeviation)
{
	return Engine.RandGaussianClamped(Min, Max, Mean, StandardDeviation);
}

int32 URandomEngineObject::GetInteger(const float Min, const float Max)
{
	return Engine.RandInt(Min, Max);
}

bool URandomEngineObject::GetBool(const float Probability01)
{
	return Engine.RandBool(Probability01);
}

UObject* URandomEngineObject::GetRandomSelection(const TArray<UObject*>& ObjectArray)
{
	const int32 Num = ObjectArray.Num();
	if (Num == 0)
	{
		return nullptr;
	}
	return ObjectArray[Engine.RandInt(0, Num - 1)];
}
