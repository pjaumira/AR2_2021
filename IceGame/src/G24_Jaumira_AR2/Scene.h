#pragma once
#include "InputManager.h"

class Scene
{
	SceneState state;
	int level;

public:
	virtual void Update(InputManager*) = 0;
	virtual void Draw() = 0;

	const SceneState* GetState()const { return &state; }
};