#include "HUD.h"

HUD::HUD(int _limitTime)
{
	lastTime = clock();
	limitTime = _limitTime;

	movesP1 = movesP2 = -1;

	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, "../../res/ttf/game_over.ttf", 60));

	Renderer::GetInstance()->LoadTexture(T_BG, "../../res/img/Background_TopoBar.png");
	Renderer::GetInstance()->LoadRect(T_BG, Rect(0, 0, SCREEN_WIDTH, 80));
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
		Renderer::GetInstance()->LoadRect(PLAYER_1_TEXT, Rect(20, 5, movesP1Size));
	}
	if (movesP2 != mP2)
	{
		movesP2 = mP2;

		std::string tmp = FillDigits(movesP2, 2);
		movesP2Size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text(PLAYER_2_TEXT, "Pl 2 moves: " + tmp, Color(0, 0, 0, 255)));
		Renderer::GetInstance()->LoadRect(PLAYER_2_TEXT, Rect(20, movesP1Size.y, movesP2Size));
	}
}

void HUD::Draw()
{
	//BACKGROUND
	Renderer::GetInstance()->PushImage(T_BG, T_BG);

	//TIMER
	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, "../../res/ttf/game_over.ttf", 100));
	
	std::string tmp = FillDigits(cTime.sec, 2);
	Color c(200, 200, 0, 255);
	Vec2 size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text(TIMER, tmp + " sec.", c));
	Renderer::GetInstance()->LoadRect(TIMER, Rect(SCREEN_WIDTH / 2 + size.x / 3, 10, size));

	Renderer::GetInstance()->PushImage(TIMER, TIMER);

	//MOVEMENTS
	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, "../../res/ttf/game_over.ttf", 60));

	Renderer::GetInstance()->PushImage(PLAYER_1_TEXT, PLAYER_1_TEXT);
	Renderer::GetInstance()->PushImage(PLAYER_2_TEXT, PLAYER_2_TEXT);
}
