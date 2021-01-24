#pragma once
#include "InputManager.h"
#include "Scene.h"

class Menu: public Scene
{


public:
	Menu();
	
	void Update(InputManager*);
	void Draw();
};