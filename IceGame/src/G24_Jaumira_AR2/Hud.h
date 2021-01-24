#pragma once
#include "Renderer.h"
#include "Types.h"
#include "Utils.h"
#include <time.h>

class HUD
{
	float limitTime;
	Time cTime;
	clock_t lastTime;
	int movesP1{ 0 }, movesP2{ 0 };

	Vec2 movesP1Size, movesP2Size;

public:
	HUD() {}
	HUD(int);
	
	void UpdateCurrentTime();
	void Update(int, int);

	void Draw();

	const float* GetTime()const { return &limitTime; }
};