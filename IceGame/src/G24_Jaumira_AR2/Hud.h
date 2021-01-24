#pragma once
#include "Renderer.h"
#include "Type.h"

class HUD {

	float currentTime;
	Time cTime;
	int movesP1, movesP2;

public:
	HUD() {}
	HUD(int, int);
	void Update(Time, int, int, int, int);

	void Draw();

	const float* GetCurrent_Time()const { return &currentTime; }
};