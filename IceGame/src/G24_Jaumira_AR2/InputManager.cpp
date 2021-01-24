#include "InputManager.h"
#include "InputManager.h"

Inputs::~Inputs()
{
	SDL_Quit();
}

void Inputs::SetKey(InputKeys key, bool pressed)
{
	keyboard[(int)key] = pressed;
}

void Inputs::Update(GameState _state)
{
	Vec2 temp;
	SDL_Event events;
	click = false;
	while (SDL_PollEvent(&events)) {

		switch (_state) {

		case GameState::MENU:
			switch (events.type) {

			case SDL_QUIT:
				exit = true;
				break;

			case SDL_KEYUP:
				switch (events.key.keysym.sym) {

				case SDLK_ESCAPE:
					keyboard[(int)InputKeys::ESC] = true;
					break;
				}
				break;

			case SDL_MOUSEMOTION:
				temp.x = events.motion.x;
				temp.y = events.motion.y;
				mousePosition = temp;
				click = false;
				break;

			case SDL_MOUSEBUTTONUP:
				if (click == false){

					temp.x = events.motion.x;
					temp.y = events.motion.y;
					mousePosition = temp;
					click = true;
				}
				break;
			}
			break;

		case GameState::PLAY:
			switch (events.type) {

			case SDL_QUIT:
				exit = true;
				break;

			case SDL_KEYDOWN:
				switch (events.key.keysym.sym) {

				case SDLK_w:
					keyboard[(int)InputKeys::UP_P1] = true;
					break;

				case SDLK_a:
					keyboard[(int)InputKeys::LEFT_P1] = true;
					break;

				case SDLK_s:
					keyboard[(int)InputKeys::DOWN_P1] = true;
					break;

				case SDLK_d:
					keyboard[(int)InputKeys::RIGHT_P1] = true;
					break;

				}
				break;

			case SDL_KEYUP:
				switch (events.key.keysym.sym) {

				case SDLK_ESCAPE:
					keyboard[(int)InputKeys::ESC] = true;
					break;

				case SDLK_w:
					keyboard[(int)InputKeys::UP_P1] = false;
					break;

				case SDLK_a:
					keyboard[(int)InputKeys::LEFT_P1] = false;
					break;

				case SDLK_s:
					keyboard[(int)InputKeys::DOWN_P1] = false;
					break;

				case SDLK_d:
					keyboard[(int)InputKeys::RIGHT_P1] = false;
					break;
				}
				break;
			}
			break;
		}
	}
}
