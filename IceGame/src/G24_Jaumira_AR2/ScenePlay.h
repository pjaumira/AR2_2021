#pragma once
#include "InputManager.h"
#include "Scene.h"

class Play:public Scene
{


public:
	Play();

	void Update(InputManager*);
	void Draw();
};