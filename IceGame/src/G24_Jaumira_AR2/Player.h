#pragma once
#include "Type.h"
#include <iostream>
#include "InputManager.h"
#include "Renderer.h"
#include "Board.h"
#include <string>
#include <time.h>

class Player
{
	Rect position, rect;
	std::string textureID;

	Vec2 initPos, mapPos, initMapPos;

	int remainingMoves;

	Direction dir;

	bool isAtGoal;
	clock_t powerPickedTime, bombSpawnTime, deathTime;

public:

	Player(std::string, std::string, Vec2, int);

	void AddScore(int);
	void Update(Inputs*, Board*);
	void Draw();

	const Vec2* GetPosition()const { return new Vec2(position.x, position.y); }
	const std::string* GetID()const { return &textureID; }
};