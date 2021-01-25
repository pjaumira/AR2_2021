#pragma once
#include "Types.h"
#include "Renderer.h"
#include <string>

class Button
{
	Rect rect;
	Text text;
	Font font;
	std::string buttonState;


public:
	Button() {}
	void SetTextData(Vec2, std::string, std::string, std::string, std::string, Color);
	void ChangeState(Vec2);
	bool Collision(Vec2);

	void Draw();
};