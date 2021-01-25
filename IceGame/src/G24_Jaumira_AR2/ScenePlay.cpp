#include "ScenePlay.h"

Play::Play(int lvl)
{
	state = SceneState::RUNNING;

	map = Map(lvl);

	hud = HUD(*map.GetLimitTime());

	players.push_back(Player(T_PLAYER_1, "../../res/img/player.png", *map.GetPlayerPosition(0), *map.GetPlayerMoves(0)));
	players.push_back(Player(T_PLAYER_2, "../../res/img/player2.png", *map.GetPlayerPosition(1), *map.GetPlayerMoves(1)));
}

void Play::Update(Inputs* inputs)
{
	if (*inputs->GetKey(InputKeys::ESC))
		state = SceneState::GOTOMENU;
	if (*inputs->GetExit())
		state = SceneState::EXIT;
	if (state == SceneState::RUNNING)
	{
		for(Player p:players)
		{
			p.Update(inputs, &map);
		}

		hud.Update(*players[0].GetRemainingMoves(), *players[1].GetRemainingMoves());
	}
	
}

void Play::Draw()
{
	Renderer::GetInstance()->Clear();

	map.Draw();
	hud.Draw();

	for (Player p : players)
	{
		p.Draw();
	}

	Renderer::GetInstance()->Render();
}
