// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "System/RandomEngine.h"

class FMersenneTwisterRandomModule : public IModuleInterface
{
	RandomEngine* Engine = nullptr;

public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
