#include "SceneRanking.h"

//Constructors
Ranking::Ranking() {

	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, F_GAMEOVER_P, 80));
	// Carga BG
	Renderer::GetInstance()->LoadRect(T_BG, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	//Crear Textos pantalla Input
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, Text( "txtPlayers", "Top Players",Color( 0,255,255,229 ) )); //Text top Players
	//Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text("txtInsert", "Insert Your Name",Color(255,255,255,229))); //Text insert your name
	//Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text("spcSend", "Press Space To Send",Color(255,255,255,229) )); // Text send

	//Button Back
	returnMenu.SetTextData(Vec2(SCREEN_WIDTH / 2, 540), F_SAIYAN_P, "Go Back", F_SAIYAN, BTTN_BACK_R, Color(255, 255, 255, 255));
	returnMenu.SetTextData(Vec2(SCREEN_WIDTH / 2, 540), F_SAIYAN_P, "Go Back", F_SAIYAN, BTTN_BACK_R_H, Color(0, 200, 0, 255));

	Load();
}

Ranking::Ranking(int _score, Inputs* inputs) {

	Renderer::GetInstance()->LoadFont(Font(F_GAMEOVER, F_GAMEOVER_P, 50));
	// Carga BG
	Renderer::GetInstance()->LoadRect(T_BG, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, Text( "txtInsert", "Insert Your Name",Color(255,255,255,229)));
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text( "spcSend", "Press Space To Send",Color(255,255,255,229) ));

	//Crear Textos pantalla Input
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, Text("txtPlayers", "Top Players", Color(0, 255, 255, 229))); //Text top Players
	//Button Back
	returnMenu.SetTextData(Vec2(SCREEN_WIDTH / 2, 540), F_SAIYAN_P, "Go Back", F_SAIYAN, BTTN_BACK_R, Color(255, 255, 255, 255));
	returnMenu.SetTextData(Vec2(SCREEN_WIDTH / 2, 540), F_SAIYAN_P, "Go Back", F_SAIYAN, BTTN_BACK_R_H, Color(0, 200, 0, 255));

	while (!NameRecord.empty()) {//We clean the name of the record
		NameRecord.pop_back();
	}

	Score = _score;
	nameInput = true;

	inputs->SetInputName(true);
}

// Guardem les dades registrades al fitxer binari extern
void Ranking::Save(int score, std::string name) {

	Load();

	if (list.empty()) { list.push_front({ name, score }); }

	else 
	{
		listofPair::iterator it2 = list.end();
		--it2;
		for (listofPair::iterator it = list.begin(); it != list.end(); ++it) 
		{
			if (it->second <= score) 
			{
				list.insert(it, { name, score });//INSERT NEW RECORD
				break;
			}
			else 
			{
				if (it == it2) 
				{
					list.push_back({ name, score });//INSERT NEW RECORD IN THE LAST POSITION
					break;
				}
			}
		}
	}

	if (list.size() > 5) 
	{// if the list is greater than 5, delete the last one
		list.pop_back();
	}

	//SAVE IN F
	std::ofstream fexit(BINARY_P, std::ios::out | std::ios::binary);

	//SAVE IN FB
	size_t len;
	for (listofPair::iterator it = list.begin(); it != list.end(); ++it)
	{
		len = it->first.size();
		fexit.write(reinterpret_cast<char*>(&len), sizeof(size_t)); //SAVE NAME
		fexit.write(it->first.c_str(), it->first.size());//SAVE NAME											
		fexit.write(reinterpret_cast<char*>(&it->second), sizeof(it->second));//SAVE RECORD
	}

	fexit.close();
}

// Carreguem les dades desde el fitxer extern a la pantalla
void Ranking::Load() {

	//READ DOC
	std::ifstream fentry(BINARY_P, std::ios::in | std::ios::binary);

	int count = 0;
	size_t len;
	char* temp;

	list.clear();

	for (int i = 0; i < 5; i++)
	{
		list.push_front({ "-",-1 });
	}

	fentry.seekg(0, std::ios::end); //Put the cursor at end

	if (fentry.tellg() > 0) 
	{
		fentry.seekg(0, std::ios::beg); //Put the cursor at first

		for (listofPair::iterator it = list.begin(); count < 5; ++it) 
		{
			fentry.read(reinterpret_cast<char*>(&len), sizeof(size_t));
			//std::cout << len << std::endl;
			temp = new char[len + 1];
			fentry.read(temp, len);
			temp[len] = '\0';
			it->first = temp;

			fentry.read(reinterpret_cast<char*>(&it->second), sizeof(it->second));

			count++;
		}

		listofPair::iterator it;
		it = list.end();
		--it;

		while (it->second <= -1) 
		{
			list.pop_back();
			it = list.end();
			--it;
		}
	}

	fentry.close();
}

void Ranking::Update(Inputs* inputs) 
{
	if (*inputs->GetKey(InputKeys::ESC))
		state = SceneState::GOTOMENU;

	if (*inputs->GetExit())
		state = SceneState::EXIT;

	// Boto per tornar al Menu
	returnMenu.ChangeState(*inputs->GetMousePosition());
	if (returnMenu.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked()) state = SceneState::GOTOMENU;

	if (nameInput) {
		if (NameRecord.size() < 5 && !keypressedNames) {
			char tmp = *inputs->GetName();
			if (tmp != '0') {
				NameRecord.push_back(tmp); //We add the pressed key
				keypressedNames = true;
				inputs->SetInputName(false);
			}
		}

		if(keypressedNames) {
			currentTime++;
			if (currentTime > 10) { 
				keypressedNames = false; 
				inputs->SetInputName(true);
				currentTime = 0;
			}
		}

		if (*inputs->GetKey(InputKeys::BACKSPACE) && !NameRecord.empty())  { //Delete last key enter
			NameRecord.pop_back();
		}

		// tenca la introduccio de noms
		if (*inputs->GetKey(InputKeys::SPACEBAR)) 
		{
			if (NameRecord.size() > 0) 
			{
				name = "";
				for (std::list<char>::iterator it = NameRecord.begin(); it != NameRecord.end(); ++it)
				{
					name += *it;
				}

				Save(Score, name);
				nameInput = false;

			}
		}
	}
}

void Ranking::DrawRanking() 
{
	int numberRecord = 1;//Number record
	int distance = 67;//Distance of records

	Vec2 size;

	if (list.size() > 0) {
		for (listofPair::iterator it = list.begin(); it != list.end(); ++it) {
			//We load the name
			size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text( "scrRanking", it->first,Color( 250,102,0,0 )));

			//We paint the name
			Renderer::GetInstance()->LoadRect("scrRanking", Rect(SCREEN_WIDTH - 350, 70 + numberRecord * distance, size));
			Renderer::GetInstance()->PushImage("scrRanking", "scrRanking");

			//We load the score
			if(it->second > 0)
				size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER , Text("scrRanking", std::to_string(it->second), Color(250, 102, 0, 0)));
			else
				size = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text("scrRanking", "-", Color(250, 102, 0, 0)));

			//Paint the score
			Renderer::GetInstance()->LoadRect("scrRanking", Rect(SCREEN_WIDTH /2 +50, 70 + numberRecord * distance, size));
			Renderer::GetInstance()->PushImage("scrRanking", "scrRanking");
			numberRecord++;
		}
	}
}

void Ranking::DrawName() {
	name = " ";
	for (std::list<char>::iterator it = NameRecord.begin(); it != NameRecord.end(); ++it) {
		name += *it;
	}
	if (name.size() > 1) name.erase(name.begin());
	Vec2 size = Renderer::GetInstance()->LoadTextureText(F_SAIYAN, Text("scrRanking", name, Color(250, 102, 0, 0)));
	Renderer::GetInstance()->LoadRect("scrRanking", Rect(SCREEN_WIDTH - 263, SCREEN_HEIGHT/2 -10, size));
	Renderer::GetInstance()->PushImage("scrRanking", "scrRanking");
}

void Ranking::Draw() 
{

	Renderer::GetInstance()->Clear();

	Renderer::GetInstance()->PushImage(T_BG, T_BG);

	if (!nameInput) {

		DrawRanking();

		// Text Players
		Vec2 tempSize = Renderer::GetInstance()->GetTextureSize("txtPlayers");

		Renderer::GetInstance()->LoadRect("txtPlayers", Rect( SCREEN_WIDTH - 340,60,tempSize.x, tempSize.y ));
		Renderer::GetInstance()->PushImage("txtPlayers", "txtPlayers");

		returnMenu.Draw();
	}

	else {

		Renderer::GetInstance()->LoadRect("txtInsert", Rect( SCREEN_WIDTH/2 -190,60,(Renderer::GetInstance()->GetTextureSize("txtInsert")).x, (Renderer::GetInstance()->GetTextureSize("txtInsert")).y ));
		Renderer::GetInstance()->LoadRect("spcSend", Rect( SCREEN_WIDTH/2 - 90 ,SCREEN_HEIGHT -100,(Renderer::GetInstance()->GetTextureSize("spcSend")).x, (Renderer::GetInstance()->GetTextureSize("spcSend")).y ));

		Renderer::GetInstance()->PushImage("txtInsert", "txtInsert");
		Renderer::GetInstance()->PushImage("spcSend", "spcSend");

		DrawName();

	}

	Renderer::GetInstance()->Render();
}