#include "SceneMenu.h"

#pragma region Menu
Menu::Menu() {

	state = SceneState::RUNNING;

	Renderer::GetInstance()->LoadTexture(T_BG, "../../res/img/Background_TopoBar.png");
	Renderer::GetInstance()->LoadRect(T_BG, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

#pragma region Buttons

	Renderer::GetInstance()->LoadFont(Font(F_SAIYAN_TITLE, F_SAIYAN_P, 100));
	Renderer::GetInstance()->LoadFont(Font(F_SAIYAN, F_SAIYAN_P, 60));
	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, F_SAIYAN_P, 80));

	//Title
	title.SetTextData(Vec2(SCREEN_WIDTH / 2, 110), F_SAIYAN_P, "ICE", F_SAIYAN_TITLE, TITLE_TEXT, Color(0, 255, 255, 255));

	//Level 1
	level1.SetTextData(Vec2(SCREEN_WIDTH / 2, title.GetRect()->y + title.GetRect()->h + 50), F_SAIYAN_P, "Level I", F_SAIYAN, BTTN_LVL_1_H, Color(0, 200, 0, 255));
	level1.SetTextData(Vec2(SCREEN_WIDTH / 2, title.GetRect()->y + title.GetRect()->h + 50), F_SAIYAN_P, "Level I", F_SAIYAN, BTTN_LVL_1, Color(255, 255, 255, 255));

	//Level2
	level2.SetTextData(Vec2(SCREEN_WIDTH / 2, level1.GetRect()->y + level1.GetRect()->h + 30), F_SAIYAN_P, "Level II", F_SAIYAN, BTTN_LVL_2_H, Color(0, 200, 0, 255));
	level2.SetTextData(Vec2(SCREEN_WIDTH / 2, level1.GetRect()->y + level1.GetRect()->h + 30), F_SAIYAN_P, "Level II", F_SAIYAN, BTTN_LVL_2, Color(255, 255, 255, 255));

	//Ranking
	ranking.SetTextData(Vec2(SCREEN_WIDTH / 2, level2.GetRect()->y + level2.GetRect()->h + 30), F_SAIYAN_P, "Ranking", F_SAIYAN, BTTN_RANKING_H, Color(0, 200, 0, 255));
	ranking.SetTextData(Vec2(SCREEN_WIDTH / 2, level2.GetRect()->y + level2.GetRect()->h + 30), F_SAIYAN_P, "Ranking", F_SAIYAN, BTTN_RANKING, Color(255, 255, 255, 255));

	//Exit
	exit.SetTextData(Vec2(SCREEN_WIDTH / 2, ranking.GetRect()->y + ranking.GetRect()->h + 30), F_SAIYAN_P, "Exit", F_SAIYAN, BTTN_EXIT_H, Color(0, 200, 0, 255));
	exit.SetTextData(Vec2(SCREEN_WIDTH / 2, ranking.GetRect()->y + ranking.GetRect()->h + 30), F_SAIYAN_P, "Exit", F_SAIYAN, BTTN_EXIT, Color(255, 255, 255, 255));

#pragma endregion
}

void Menu::Update(Inputs* inputs) {

	if (*inputs->GetKey(InputKeys::ESC) || *inputs->GetExit())
		state = SceneState::EXIT;

#pragma region Buttons

#pragma region Level_1

	level1.ChangeState(*inputs->GetMousePosition());
	if (level1.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked())
		state = SceneState::GOTOLEVEL1;

#pragma endregion

#pragma region Level_2

	level2.ChangeState(*inputs->GetMousePosition());
	if (level2.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked())
		state = SceneState::GOTOLEVEL2;

#pragma endregion

#pragma region Ranking

	ranking.ChangeState(*inputs->GetMousePosition());
	if (ranking.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked())
		state = SceneState::GOTORANKING;

#pragma endregion

#pragma region Exit

	exit.ChangeState(*inputs->GetMousePosition());
	if (exit.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked())
		state = SceneState::EXIT;

#pragma endregion

#pragma endregion
}

void Menu::Draw() {

	Renderer::GetInstance()->Clear();
	Renderer::GetInstance()->PushImage(T_BG, T_BG);

	title.Draw();
	level1.Draw();
	level2.Draw();
	ranking.Draw();
	exit.Draw();

	Renderer::GetInstance()->Render();
}

#pragma endregion