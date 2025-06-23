// Copyright Epic Games, Inc. All Rights Reserved.

#include "Blueprint/RandomEngineBPLibrary.h"
#include "System/RandomEngine.h"

URandomEngineBPLibrary::URandomEngineBPLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float URandomEngineBPLibrary::RandomEngineSampleFunction(float Param)
{
	return -1;
}

FGuid URandomEngineBPLibrary::RandomNewGUID()
{
	return RandomEngine::StaticNewGuid();
}
