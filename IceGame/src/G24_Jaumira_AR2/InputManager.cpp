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
	rkgChar = '0';
	if(keyboard[(int)InputKeys::BACKSPACE])
		keyboard[(int)InputKeys::BACKSPACE] = false;
	Vec2 temp;
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
				if (click == false) {

					temp.x = events.motion.x;
					temp.y = events.motion.y;
					mousePosition = temp;
					click = true;
				}
				break;
			}
			break;
		case GameState::RANKING:
			switch (events.type) {

			case SDL_QUIT:
				exit = true;
				break;
			case SDL_KEYDOWN:
				if (inputName)
				{
					if (events.key.keysym.sym >= SDLK_a && events.key.keysym.sym <= SDLK_z)
						rkgChar = events.key.keysym.sym;
					else if(events.key.keysym.sym == SDLK_SPACE)
						keyboard[(int)InputKeys::SPACEBAR] = true;
					else if(events.key.keysym.sym == SDLK_BACKSPACE)
						keyboard[(int)InputKeys::BACKSPACE] = true;
				}
				break;
			case SDL_KEYUP:
				switch (events.key.keysym.sym) {

				case SDLK_ESCAPE:
					keyboard[(int)InputKeys::ESC] = true;
					break;
				case SDLK_SPACE:
					keyboard[(int)InputKeys::SPACEBAR] = false;
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
					keyboard[(int)InputKeys::UP] = true;
					break;

				case SDLK_a:
					keyboard[(int)InputKeys::LEFT] = true;
					break;

				case SDLK_s:
					keyboard[(int)InputKeys::DOWN] = true;
					break;

				case SDLK_d:
					keyboard[(int)InputKeys::RIGHT] = true;
					break;

				}
				break;

			case SDL_KEYUP:
				switch (events.key.keysym.sym) {

				case SDLK_ESCAPE:
					keyboard[(int)InputKeys::ESC] = true;
					break;

				case SDLK_w:
					keyboard[(int)InputKeys::UP] = false;
					break;

				case SDLK_a:
					keyboard[(int)InputKeys::LEFT] = false;
					break;

				case SDLK_s:
					keyboard[(int)InputKeys::DOWN] = false;
					break;

				case SDLK_d:
					keyboard[(int)InputKeys::RIGHT] = false;
					break;
				}
				break;
			}
			break;
		}
	}
}

void Inputs::SetInputName(bool input)
{
	inputName = input;
}
