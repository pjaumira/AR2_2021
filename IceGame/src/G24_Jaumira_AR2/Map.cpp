#include "Map.h"

void Map::ReadXML(int lvl)
{
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	//
		//Organizar informacion
	rapidxml::xml_node<>* pRoot = doc.first_node();
	for (rapidxml::xml_node<>* pNode = pRoot->first_node("Level"); pNode; pNode = pNode->next_sibling())
	{
		if (pNode->first_attribute("id")->value() == std::to_string(lvl))
		{
			pRoot = pNode;
			break;
		}
	}

	std::string s = pRoot->last_attribute()->value();
	lTime = std::stoi(s);

	int i = 0;
	//Players
	for (rapidxml::xml_node<>* pNode = pRoot->first_node("characters")->first_node(); pNode; pNode = pNode->next_sibling())
	{
		rapidxml::xml_attribute<>* pAttr = pNode->first_attribute();
		//Moves
		s = pAttr->value();
		int moves = std::stoi(s);
		
		//Position
		Vec2 pos;
		pAttr = pAttr->next_attribute();
		s = pAttr->value();
		int tmp = std::stoi(s);
		pos.y = tmp + 1;

		pAttr = pAttr->next_attribute();
		s = pAttr->value();
		tmp = std::stoi(s);
		pos.x = tmp + 1;

		playerInfo.push_back(PlayerData(pos, moves));

		pAttr = pAttr->next_attribute();
		s = pAttr->value();
		int y = std::stoi(s);

		pAttr = pAttr->next_attribute();
		s = pAttr->value();
		int x = std::stoi(s);
		if (i == 0)
			map[x + 1][y + 1] = CellType::GOAL_P1;
		else if (i == 1)
			map[x + 1][y + 1] = CellType::GOAL_P2;
		i++;
	}

	//Mapa
	for(rapidxml::xml_node<>* pNode = pRoot->first_node("Walls")->first_node(); pNode; pNode = pNode->next_sibling())
	{
		rapidxml::xml_attribute<>* pAttr = pNode->first_attribute();
		s = pAttr->value();
		int y = std::stoi(s);

		pAttr = pAttr->next_attribute();
		s = pAttr->value();
		int x = std::stoi(s);

		map[x + 1][y + 1] = CellType::WALL;
	}

	for (int i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				map[i][j] = CellType::WALL;
		}
	}
}

Map::Map(int lvl)
{
	height = (SCREEN_HEIGHT - 80) / SPRITE_RESOLUTION; 
	width = SCREEN_WIDTH / SPRITE_RESOLUTION;

	map = new CellType*[width];

	for (size_t i = 0; i < width; i++)
	{
		map[i] = new CellType[height];
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			map[i][j] = CellType::ICE;
		}
	}

	ReadXML(lvl);

	Renderer::GetInstance()->LoadTexture(T_MAP, "../../res/img/items.png");
	textureSize = Renderer::GetInstance()->GetTextureSize(T_MAP);

	textureSize.x /= 2;
	textureSize.y /= 2;

	Renderer::GetInstance()->LoadRect(T_ICE, Rect(0, 0, textureSize));
	Renderer::GetInstance()->LoadRect(T_WALL, Rect(textureSize.x, 0, textureSize));
	Renderer::GetInstance()->LoadRect(T_GOAL1, Rect(0, textureSize.y, textureSize));
	Renderer::GetInstance()->LoadRect(T_GOAL2, Rect(textureSize.x, textureSize.y, textureSize));

}

void Map::Draw()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Renderer::GetInstance()->LoadRect(ACTUAL_MAP_T, Rect(i * SPRITE_RESOLUTION, j * SPRITE_RESOLUTION + 80, SPRITE_RESOLUTION, SPRITE_RESOLUTION));
			if (map[i][j] == CellType::ICE)
				Renderer::GetInstance()->PushSprite(T_MAP, T_ICE, ACTUAL_MAP_T);
			else if (map[i][j] == CellType::WALL)
				Renderer::GetInstance()->PushSprite(T_MAP, T_WALL, ACTUAL_MAP_T);
			else if (map[i][j] == CellType::GOAL_P1)
				Renderer::GetInstance()->PushSprite(T_MAP, T_GOAL1, ACTUAL_MAP_T);
			else if (map[i][j] == CellType::GOAL_P2)
				Renderer::GetInstance()->PushSprite(T_MAP, T_GOAL2, ACTUAL_MAP_T);
		}
	}
}
