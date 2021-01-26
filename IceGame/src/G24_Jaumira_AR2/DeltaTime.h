#pragma once
#include "Types.h"
#include <time.h>

class DeltaTime
{
	float deltaTime;
	clock_t lastTime;

public:
	DeltaTime();

	void UpdateDeltaTime();

	const float* GetDeltaTime()const { return &deltaTime; }
};

