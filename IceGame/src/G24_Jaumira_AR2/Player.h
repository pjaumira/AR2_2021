#pragma once
#include "Types.h"
#include <iostream>
#include "InputManager.h"
#include "Renderer.h"
#include "Map.h"
#include <string>

class Player
{
	Rect position, rect;
	std::string textureID;

	Vec2 mapPos;

	int remainingMoves, cellsMovedCounter;
	float speed, animationTime;

	Direction dir;

	bool isAtGoal, direction[4] = {false};

public:
	Player() {};
	Player(std::string, std::string, Vec2, int);

	void Update(Inputs*, Map*, float);
	void Draw();

	const Vec2* GetPosition()const { return new Vec2(position.x, position.y); }
	const std::string* GetID()const { return &textureID; }
	const int* GetRemainingMoves()const { return &remainingMoves; }
	const bool* AtGoal()const { return &isAtGoal; }
};