#pragma once
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "HUD.h"
#include <vector>

class Play:public Scene
{
	std::vector<Player> players;
	Map map;
	HUD hud;

public:
	Play() {}
	Play(int);

	void Update(Inputs*);
	void Draw();

	const float* GetTime()const { return hud.GetTime(); }
};