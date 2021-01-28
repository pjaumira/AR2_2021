#pragma once
#include "Types.h"
#include "SDL.h"

class Inputs
{
private:
	bool keyboard[(int)InputKeys::COUNT] = {};
	Vec2 mousePosition;
	bool click = false, exit = false, inputName = false;
	SDL_Event events;
	char rkgChar = '0';

public:

	~Inputs();
	void SetKey(InputKeys, bool);
	void Update(GameState);
	void SetInputName(bool);

	const bool* GetKey(InputKeys key)const { return &keyboard[(int)key]; }
	const Vec2* GetMousePosition()const { return &mousePosition; }
	const bool* GetMouseClicked()const { return &click; }
	const char* GetName()const { return &rkgChar; }
	const bool* GetExit()const { return &exit; }
};