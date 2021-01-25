#pragma once
#include "Scene.h"

class Menu: public Scene
{


public:
	Menu();
	
	void Update(Inputs*);
	void Draw();
};