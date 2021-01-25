#include "Game.h"

Game::Game()
{
	state = GameState::PLAY;
	scene = new Play(2);
}

void Game::Run()
{
	while (state != GameState::EXIT)
	{
		inputs.Update(state);
		switch (state)
		{
		case GameState::MENU:
			if (*scene->GetState() == SceneState::GOTOLEVEL1)
			{
				state = GameState::PLAY;
				delete scene;
				scene = new Play(1);
			}
			else if (*scene->GetState() == SceneState::GOTOLEVEL2)
			{
				state = GameState::PLAY;
				delete scene;
				scene = new Play(2);
			}
			else if (*scene->GetState() == SceneState::EXIT)
			{
				state = GameState::EXIT;
			}
			break;
		case GameState::PLAY:
			if (*scene->GetState() == SceneState::GOTOMENU)
			{
				/*
				state = GameState::Menu;
				delete scene;
				scene = new Menu();
				*/
				state = GameState::EXIT;
			}
			else if (*scene->GetState() == SceneState::EXIT)
			{
				state = GameState::EXIT;
			}
			break;
		case GameState::RANKING:
			if (*scene->GetState() == SceneState::EXIT)
			{
				state = GameState::EXIT;
			}
			break;
		}
		scene->Update(&inputs);
		scene->Draw();
	}
}