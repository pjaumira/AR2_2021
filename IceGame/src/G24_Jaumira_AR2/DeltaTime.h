#pragma once
#include "Types.h"
#include <time.h>

class DeltaTime
{
	Time t;
	float deltaTime;
	clock_t lastTime;

public:
	DeltaTime();

	void UpdateDeltaTime();
	void SecondsToMinutes(float _t);

	const Time* GetTime()const { return &t; }
	const float* GetDeltaTime()const { return &deltaTime; }
};

