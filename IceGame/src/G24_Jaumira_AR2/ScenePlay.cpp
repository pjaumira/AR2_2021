#include "ScenePlay.h"

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
