#pragma once
#include <string>
#include <unordered_map>

#define SCREEN_WIDTH 432
#define SCREEN_HEIGHT 584
#define SPRITE_RESOLUTION 72

const int FPS = 60;

// Texture Constants
const std::string T_BG = "Background";
const std::string T_ITEMS = "Items";
const std::string T_PLAYER_1 = "Player_1";
const std::string T_PLAYER_1_RECT = "Player_1_Rect";
const std::string T_PLAYER_2 = "Player_2";
const std::string T_PLAYER_2_RECT = "Player_2_Rect";

const std::string T_MAP = "Map_Textures";
const std::string ACTUAL_MAP_T = "ActualTexture";

const std::string T_WALL = "Wall";
const std::string T_GOAL1 = "Goal1";
const std::string T_GOAL2 = "Goal2";
const std::string T_ICE = "Ice";

//Fonts
const std::string F_GAMEOVER = "GameOver_font";
const std::string F_SAIYAN = "Saiyan_font";
const std::string F_SAIYAN_TITLE = "Saiyan_font_title";
const std::string F_SAIYAN_P = "../../res/ttf/saiyan.ttf";
const std::string F_GAMEOVER_P = "../../res/ttf/game_over.ttf";

// Fitxers
const std::string BINARY_P = "../../res/files/ranking.bin";
const std::string XML_P = "../../res/files/config.xml";

//Text Menu
const std::string TITLE_TEXT = "Title_txt";
const std::string BTTN_LVL_1 = "Level1_Button";
const std::string BTTN_LVL_1_H = "Level1_Button_Hover";
const std::string BTTN_LVL_2 = "Level2_Button";
const std::string BTTN_LVL_2_H = "Level2_Button_Hover";
const std::string BTTN_RANKING = "Ranking_Button";
const std::string BTTN_RANKING_H = "Ranking_Button_Hover";
const std::string BTTN_MENU = "Menu_Button";
const std::string BTTN_MENU_H = "Menu_Button_Hover";
const std::string BTTN_EXIT = "Exit_Button";
const std::string BTTN_EXIT_H = "Exit_Button_Hover"; 
const std::string BTTN_BACK_R = "Ranking_Button";
const std::string BTTN_BACK_R_H = "Ranking_Button_Hover";

// Text Ranking
const std::string RANKING_INDEX = "Index_Ranking";
const std::string RANKING = "_Ranking";

// Text Play
const std::string TIMER = "Timer";
const std::string PLAYER_1_TEXT = "Text_Player_1";
const std::string PLAYER_2_TEXT = "Text_Player_2";