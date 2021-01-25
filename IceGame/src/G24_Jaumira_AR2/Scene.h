#pragma once
#include "InputManager.h"
#include <vector>
#include "DeltaTime.h"
#include "Player.h"
#include "Board.h"
#include "Button.h"
#include "HUD.h"
#include "Utils.h"

//Definicio classe Scene
class Scene {

public:

	SceneState state;
	int level;

	virtual void Update(Inputs*) = 0;
	virtual void Draw() = 0;

	const SceneState* GetState()const { return &state; }
};
