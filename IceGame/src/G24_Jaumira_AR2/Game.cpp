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
			else if (*scene->GetState() == SceneState::GOTORANKING)
			{
				state = GameState::RANKING;
				delete scene;
				scene = new Ranking();
			}
			else if (*scene->GetState() == SceneState::EXIT)
			{
				state = GameState::EXIT;
			}
			break;
		case GameState::PLAY:
			if (*scene->GetState() == SceneState::GOTOMENU)
			{
				state = GameState::MENU;
				delete scene;
				scene = new Menu();
				inputs.SetKey(InputKeys::ESC, false);
			}
			else if (*scene->GetState() == SceneState::GOTORANKING)
			{
				int i = *scene->GetTime();
				state = GameState::RANKING;
				delete scene;
				scene = new Ranking(i);
			}
			else if (*scene->GetState() == SceneState::EXIT)
			{
				state = GameState::EXIT;
			}
			break;
		case GameState::RANKING:
			if (*scene->GetState() == SceneState::GOTOMENU)
			{
				state = GameState::MENU;
				delete scene;
				scene = new Menu();
				inputs.SetKey(InputKeys::ESC, false);
			}
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