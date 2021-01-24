#pragma once
#include "InputManager.h"
#include "Scene.h"
#include "SceneMenu.h"
#include "ScenePlay.h"
#include "SceneRanking.h"
#include "Types.h"

class Game
{
	GameState state;
	Scene* scene;
	InputManager inputs;

public:
	Game();

	void Run();
};