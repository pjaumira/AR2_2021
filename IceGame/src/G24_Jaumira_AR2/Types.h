#pragma once
#include <time.h>
#include <string>
#include <stdint.h>

struct Vec2
{
	int x, y;

	Vec2() {};
	Vec2(int _x, int _y) { x = _x; y = _y; };

};

struct Rect
{
	int x, y, w, h;

	Rect() {};
	Rect(int _x, int _y) :x(_x), y(_y), w(0), h(0) {};
	Rect(int _x, int _y, int _w, int _h) { x = _x; y = _y; w = _w; h = _h; };
	Rect(Vec2 _pos, int _w, int _h) { x = _pos.x; y = _pos.y; w = _w; h = _h; };
	Rect(Vec2 _pos, Vec2 _size) { x = _pos.x; y = _pos.y; w = _size.x; h = _size.y; };
	Rect(int _x, int _y, Vec2 _size) { x = _x; y = _y; w = _size.x; h = _size.y; };
};

struct Font
{
	std::string id;
	std::string path;
	int size;

	Font() {}
	Font(std::string _id, std::string _path, int _size) :id(_id), path(_path), size(_size) {};
};

struct Color
{
	uint8_t g = 0, 
		r = 0,
		b = 0,
		a = 0;

	Color() {};
	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :r(_r), g(_g), b(_b), a(_a) {};
};

struct Text
{
	std::string id;
	std::string text;
	Color color;

	Text() {}
	Text(std::string _id, std::string _text, Color _color) :id(_id), text(_text), color(_color) {};
};

enum class InputKeys{ UP_P1, DOWN_P1, RIGHT_P1, LEFT_P1, UP_P2, DOWN_P2, RIGHT_P2, LEFT_P2, ESC, SPACE, RCTRL, COUNT };

enum class Direction { UP, DOWN, LEFT, RIGHT, UP_STOP, DOWN_STOP, LEFT_STOP, RIGHT_STOP, NONE };

enum class GameState { MENU, PLAY, RANKING, EXIT, COUNT };

enum class SceneState {RUNNING, GAMEOVER, GOTOMENU, GOTOLEVEL1, GOTOLEVEL2, GOTORANKING, EXIT, COUNT};

enum class CellType {PLAYER_1, PLAYER_2, WALL, BREAKABLE_WALL, LIMIT_WALL, DESTR_WALL, BOMB, ROLLER_SKATES, HELMET, COUNT};

enum class BombState {EXPLODED, FINISHED, FADEOUT, COUNT};

struct Time
{
	int sec, min, h;
	Time() {}
	Time(int _s, int _m, int _h) :sec(_s), min(_m), h(_h) {}
};