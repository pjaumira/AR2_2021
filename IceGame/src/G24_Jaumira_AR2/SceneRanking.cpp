#include "SceneRanking.h"
#include "Renderer.h"

//Constructors
Ranking::Ranking() {

	// Load Font (Arial i Game_Over)
	Renderer::GetInstance()->LoadFont({ F_GAMEOVER, F_GAMEOVER_P, 120 }); //TITLE
	Renderer::GetInstance()->LoadFont({ F_SAIYAN, F_SAIYAN_P, 35 }); //

	//Crear Textos pantalla Input
	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { "txtPlayers", "Top Players",{ 255,255,255,229 } }); //Text top Players
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { "txtInsert", "Insert Your Name",{ 255,255,255,229 } }); //Text insert your name
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { "spcSend", "Press Space To Send",{ 255,255,255,229 } }); // Text send

	//Button Back
	returnMenu.SetTextData(Vec2(SCREEN_WIDTH / 2, 340), F_SAIYAN_P, "Go Back", F_SAIYAN, BTTN_BACK_R, Color(0, 150, 0, 255));

	Load();
}

Ranking::Ranking(int _score) {

	Renderer::GetInstance()->LoadFont({ F_GAMEOVER, F_GAMEOVER_P, 60 }); //TITLE
	Renderer::GetInstance()->LoadFont({ F_SAIYAN, F_SAIYAN_P, 50 }); //

	Renderer::GetInstance()->LoadTextureText(F_SAIYAN, { "txtInsert", "Insert Your Name",{ 255,255,255,229 } });
	Renderer::GetInstance()->LoadTextureText("Arial", { "spcSend", "Press Space To Send",{ 255,255,255,229 } });

	while (!NameRecord.empty()) {//We clean the name of the record
		NameRecord.pop_back();
	}

	Score = _score;
	nameInput = true;
}

// Guardem les dades registrades al fitxer binari extern
void Ranking::Save(int score, std::string name) {

	Load();

	if (list.empty()) {
		list.push_front({ name, score });
	}

	else {
		listofPair::iterator it2 = list.end();
		--it2;
		for (listofPair::iterator it = list.begin(); it != list.end(); ++it) {
			if (it->second <= score) {
				list.insert(it, { name, score });//INSERT NEW RECORD
				break;
			}
			else {
				if (it == it2) {
					list.push_back({ name, score });//INSERT NEW RECORD IN THE LAST POSITION
					break;
				}
			}
		}
	}

	if (list.size() > 5) {// if the list is greater than 5, delete the last one
		list.pop_back();
	}

	//SAVE IN F
	std::ofstream fexit(BINARY_P, std::ios::out | std::ios::binary);

	//SAVE IN FB
	size_t len;
	for (listofPair::iterator it = list.begin(); it != list.end(); ++it) {
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

	for (int i = 0; i < 5; i++) {
		list.push_front({ "Name",-1 });
	}

	fentry.seekg(0, std::ios::end); //Put the cursor at end

	if (fentry.tellg() > 0) {
		fentry.seekg(0, std::ios::beg); //Put the cursor at first

		for (listofPair::iterator it = list.begin(); count < 5; ++it) {
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

		while (it->second <= -1) {
			list.pop_back();
			it = list.end();
			--it;
		}
	}

	fentry.close();
}

void Ranking::Update(Inputs* inputs) {

	// Boto per tornar al Menu
	returnMenu.ChangeState(*inputs->GetMousePosition());
	if (returnMenu.Collision(*inputs->GetMousePosition()) && *inputs->GetMouseClicked()) state = SceneState::GOTOMENU;

	if (nameInput) {

		if (Renderer::GetInstance()->event.key.keysym.sym >= SDLK_a && Renderer::GetInstance()->event.key.keysym.sym <= SDLK_z && NameRecord.size() < 10 && !keypressedNames) {
			NameRecord.push_back(Renderer::GetInstance()->event.key.keysym.sym);//We add the pressed key
			keypressedNames = true;
			currentTime = 0;
			Renderer::GetInstance()->event.key.keysym.sym = 32;
		}

		currentTime++;
		if (currentTime > 50) { keypressedNames = false; }

		if (Inputs::Check()->backspace && !NameRecord.empty()) { //Delete last key enter
			NameRecord.pop_back();
			Inputs::Check()->backspace = false;
		}

		// tenca la introduccio de noms
		if (Inputs::Check()->space) {
			if (NameRecord.size() > 0) {
				name = "";
				for (std::list<char>::iterator it = NameRecord.begin(); it != NameRecord.end(); ++it) {
					name += *it;
				}

				Save(Score, name);
				nameInput = false;

				Inputs::Check()->space = false;

				state = SceneState::GOTORANKING;
				// Scene::StateScene = SceneState::GOTO;
				// Scene::gameScene = GameState::RANKING;
			}
		}
	}
}

void Ranking::DrawRanking() {
	int numberRecord = 1;//Number record
	int distance = 35;//Distance of records
	if (list.size() > 0) {
		for (listofPair::iterator it = list.begin(); it != list.end(); ++it) {

			//We load the name
			Renderer::GetInstance()->LoadTextureText("Arial", { "scrRanking", it->first,{ 250,102,0,0 } });

			//We paint the name
			Renderer::GetInstance()->LoadRect("scrRanking", { SCREEN_WIDTH - 470,120 + numberRecord * distance,(Renderer::GetInstance()->GetTextureSize("scrRanking")).x, (Renderer::GetInstance()->GetTextureSize("scrRanking")).y });
			Renderer::GetInstance()->PushImage("scrRanking", "scrRanking");

			//We load the score
			Renderer::GetInstance()->LoadTextureText("Arial", { "scrRanking", std::to_string(it->second) ,{ 250,102,0,0 } });

			//Paint the score
			Renderer::GetInstance()->LoadRect("scrRanking", { SCREEN_WIDTH - 320,120 + numberRecord * distance,(Renderer::GetInstance()->GetTextureSize("scrRanking")).x, (Renderer::GetInstance()->GetTextureSize("scrRanking")).y });
			Renderer::GetInstance()->PushImage("scrRanking", "scrRanking");
			numberRecord++;
		}
	}
}

void Ranking::DrawName() {
	name = "";
	for (std::list<char>::iterator it = NameRecord.begin(); it != NameRecord.end(); ++it) {

		name += *it;
		Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, { "scrRanking", name,{ 250,102,0,0 } });
		Renderer::GetInstance()->LoadRect("scrRanking", { 300,200,(Renderer::GetInstance()->GetTextureSize("scrRanking")).x, (Renderer::GetInstance()->GetTextureSize("scrRanking")).y });
		Renderer::GetInstance()->PushImage("scrRanking", "srcRanking");
	}
}

void Ranking::Draw() {

	if (!nameInput) {

		DrawRanking();

		// Text Players
		Renderer::GetInstance()->LoadRect("txtPlayers", { 200,60,(Renderer::GetInstance()->GetTextureSize("txtPlayers")).x, (Renderer::GetInstance()->GetTextureSize("txtPlayers")).y });
		Renderer::GetInstance()->PushImage("txtPlayers", "txtPlayers");

		returnMenu.Draw();
	}

	else {

		Renderer::GetInstance()->LoadRect("txtInsert", { 80,60,(Renderer::GetInstance()->GetTextureSize("txtInsert")).x, (Renderer::GetInstance()->GetTextureSize("txtInsert")).y });
		Renderer::GetInstance()->LoadRect("spcSend", { 200,360,(Renderer::GetInstance()->GetTextureSize("spcSend")).x, (Renderer::GetInstance()->GetTextureSize("spcSend")).y });

		Renderer::GetInstance()->PushImage("txtInsert", "txtInsert");
		Renderer::GetInstance()->PushImage("spcSend", "spcSend");

		DrawName();
	}

	Renderer::GetInstance()->Render();
	Renderer::GetInstance()->Clear();
}