#pragma once
#include "InputManager.h"
#include "Renderer.h"

class Scene
{
	SceneState state;
	int level;

public:
	virtual void Update(Inputs*) = 0;
	virtual void Draw() = 0;

	const SceneState* GetState()const { return &state; }
};