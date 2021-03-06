#pragma once
#include "Renderer.h"
#include "Types.h"
#include "Utils.h"
#include <time.h>

class HUD
{
	float limitTime = 0;
	Time cTime;
	int movesP1{ 0 }, movesP2{ 0 };

	Vec2 movesP1Size, movesP2Size;

public:
	HUD() {}
	HUD(int);
	
	void Update(int, int, float);

	void Draw();

	const float* GetTime()const { return &limitTime; }
};