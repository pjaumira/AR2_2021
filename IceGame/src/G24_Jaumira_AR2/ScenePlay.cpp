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
		for(Player &p:players)
		{
			if(!*p.AtGoal() && *p.GetRemainingMoves() > 0)
				p.Update(inputs, &map, *dt.GetDeltaTime());
		}

		hud.Update(*players[0].GetRemainingMoves(), *players[1].GetRemainingMoves(), *dt.GetDeltaTime());
		if (*hud.GetTime() <= 0.f || *players[0].GetRemainingMoves() <= 0 && *players[1].GetRemainingMoves() <= 0)
			state = SceneState::GOTOMENU;
		if (*players[0].AtGoal() && *players[1].AtGoal())
			state = SceneState::GOTORANKING;
	}
	dt.UpdateDeltaTime();
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
