#include "Game.h"

Game::Game()
{
	state = GameState::MENU;
	scene = new Menu();
}

void Game::Run()
{
	while (state != GameState::EXIT)
	{
		switch (state)
		{
		case GameState::MENU:
			break;
		case GameState::PLAY:
			break;
		case GameState::RANKING:
			break;
		}
	}
}