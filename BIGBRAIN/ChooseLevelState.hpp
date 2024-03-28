#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "DetectiveState.hpp"
#include "PenguinState.hpp"
#include "TextPenguin.hpp"
#include "TextDetective.hpp"
#include "MainMenuState.hpp"
#include "MusicState.hpp"
#include "ChooseProfileState.hpp"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

namespace Bongo
{
	class ChooseLevelState : public State
	{
	public:
		ChooseLevelState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	private:
		GameDataRef _data;
		sf::Sprite Background;

		sf::Text Instruction;
		sf::Text LevelName[NUMBER_OF_LEVELS];

		string LevelNameString[NUMBER_OF_LEVELS] = { "Level 1. Geography", "Level 2. Inventions", "Level 3. Music" };
		float LevelNamePosition[NUMBER_OF_LEVELS * 2] = { 80, 265, 460, 265, 285, 515 };

		sf::Sprite Level[NUMBER_OF_LEVELS];
		string TextureName[NUMBER_OF_LEVELS] = { "Penguin Level Texture", "Detective Level Texture", "Music Level Texture" };
		float IconPosition[NUMBER_OF_LEVELS * 2] = { 100, 100, 500, 100, 285, 350 };

		TextDetective* textdetective;
		TextPenguin* textpenguin;
		TextMusic* textmusic;

		sf::Clock _clock;
	};
}
