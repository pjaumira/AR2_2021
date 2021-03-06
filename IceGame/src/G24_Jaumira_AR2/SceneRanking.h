#pragma once
#include "Scene.h"
#include <list>
#include "DeltaTime.h"
#include "Button.h"
#include "Utils.h"
#include <sstream>
#include <fstream>

typedef std::list<std::pair<std::string, int>> listofPair;

//Definicio classe Ranking
class Ranking : public Scene {

public:

	Ranking();
	Ranking(int _score, Inputs*);
	~Ranking();

	bool nameInput = false;

	std::string name;
	std::list<char> NameRecord;
	listofPair list;

	Button returnMenu;

	int Score;

	bool keypressedEnter = false;
	bool keypressedNames = false;
	bool keypressedSpace = false;

	//save score
	void Save(int score, std::string name);

	//loading score
	void Load();

	void Update(Inputs*);
	void Draw();
	void DrawRanking();
	void DrawName();

private:

	int currentTime;
};
