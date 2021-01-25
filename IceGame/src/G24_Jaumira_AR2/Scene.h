#pragma once
#include "InputManager.h"
#include "Renderer.h"

class Scene
{
protected:


	SceneState state;
	int level;

public:
	virtual void Update(Inputs*) = 0;
	virtual void Draw() = 0;

	virtual const float* GetTime()const { return new float(-1.f); }
	const SceneState* GetState()const { return &state; }
};