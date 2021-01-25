#pragma once
#include "Scene.h"

// Definicio classe Menu
class Menu : public Scene {

	Button title, level1, level2, ranking, exit;

public:

	Menu();

	void Update(Inputs*);
	void Draw();
};