#include "HUD.h"
#include "HUD.h"
#include "HUD.h"

HUD::HUD(int _limitTime)
{
	lastTime = clock();
	limitTime = _limitTime;

	mp1 = mp2 = -1;
}

void HUD::UpdateCurrentTime()
{
	float dt = (clock() - lastTime) / CLOCKS_PER_SEC;
	lastTime = clock();
	limitTime -= dt;
}

void HUD::Update(int mp1, int mP2)
{
	UpdateCurrentTime();
	SecondsToMinutes(limitTime, cTime);			//Pasar de segons a format min:sec
	
	if (movesP1 != mp1)
	{
		movesP1 = mp1;

		std::string tmp = FillDigits(movesP1, 2);
		movesP1Size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text(PLAYER_1_TEXT, "Pl 1 moves: " + tmp, Color(0, 0, 0, 255)));
		Renderer::GetInstance()->LoadRect(PLAYER_1_TEXT, Rect(20, 10, movesP1Size));
	}
	if (movesP2 != mp2)
	{
		movesP2 = mp2;

		std::string tmp = FillDigits(movesP2, 2);
		movesP2Size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text(PLAYER_2_TEXT, "Pl 2 moves: " + tmp, Color(0, 0, 0, 255)));
		Renderer::GetInstance()->LoadRect(PLAYER_2_TEXT, Rect(20, 10 + movesP1Size.y, movesP2Size));
	}
}

void HUD::Draw()
{
#pragma region Timer
	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, "../../res/ttf/game_over.ttf", 100));
	
	std::string tmp = FillDigits(cTime.sec, 2);
	Vec2 size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text(TIMER, tmp + " sec.", Color(255, 255, 255, 255)));
	Renderer::GetInstance()->LoadRect(TIMER, Rect(SCREEN_WIDTH / 2 + size.x / 3, (SCREEN_HEIGHT - size.y) / 2, size));

	Renderer::GetInstance()->PushImage(TIMER, TIMER);
#pragma endregion

}
