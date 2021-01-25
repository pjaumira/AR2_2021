#pragma once
#include "Types.h"
#include "Constants.h"
#include "Renderer.h"
#include "../../dep/inc/xml/rapidxml.hpp"
#include "../../dep/inc/xml/rapidxml_iterators.hpp"
#include "../../dep/inc/xml/rapidxml_print.hpp"
#include "../../dep/inc/xml/rapidxml_utils.hpp"
#include <sstream>
#include <vector>

class Map
{
	int width, height, lTime;
	CellType** map;
	Vec2 textureSize;

	struct PlayerData {
		Vec2 pos;
		int moves;

		PlayerData() {};
		PlayerData(Vec2 _p, int _m) :pos(_p), moves(_m) {};
	};
	std::vector<PlayerData> playerInfo;

	void ReadXML(int);

public:
	Map() {}
	Map(int);

	void Draw();

	const int* GetPlayerMoves(int id)const { return &playerInfo[id].moves; }
	const int* GetLimitTime()const { return &lTime; }
	const Vec2* GetPlayerPosition(int id)const { return &playerInfo[id].pos; }
	const CellType* GetCellFromPos(Vec2 pos)const { return &map[pos.x][pos.y]; }
};

