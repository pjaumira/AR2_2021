#pragma once
#include "Scene.h"
#include "Button.h"
#include "Utils.h"
#include <vector>
#include "DeltaTime.h"

// Definicio classe Menu
class Menu : public Scene {

	Button title, level1, level2, ranking, exit;

public:

	Menu();

	void Update(Inputs*);
	void Draw();
};