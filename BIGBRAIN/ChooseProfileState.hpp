#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "ChooseLevelState.hpp"
#include "DetectiveState.hpp"
#include "PenguinState.hpp"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

namespace Bongo
{
	typedef struct
	{
		string Name;
		int Points;

	}PlayerProfile;

	class ChooseProfileState : public State
	{
	public:
		ChooseProfileState(GameDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void MoveUp();
		void MoveDown();

		void SaveProfiles();
		void LoadProfiles();

		void SavePlayerNumber();

		void DeleteProfile();

	private:
		GameDataRef _data;
		sf::Sprite Background;
		sf::Clock _clock;

		sf::Text ChooseOption[MAX_NUMBER_OF_PROFILES + 1];
		float ChoosePosition[(MAX_NUMBER_OF_PROFILES + 1) * 2] = {290, 120, 100, 300, 100, 400, 100, 500};
		string ChooseOptionString[MAX_NUMBER_OF_PROFILES + 1] = {"ADD PROFILE", "1.", "2.", "3." };

		sf::Text AdditionalInfo[2];
		float AdditionalPosition[4] = {170, 170, 100, 250};
		string AdditionalString[2] = { "TYPE YOUR NAME AND PRESS ENTER" , "CHOOSE EXISTING PROFILE" };

		string PlayerNames[MAX_NUMBER_OF_PROFILES];
		int PlayerPoints[MAX_NUMBER_OF_PROFILES];

		int selectID;

		string NewPlayerName;
		sf::Sprite InputField;

		PlayerProfile* playerprofile[MAX_NUMBER_OF_PROFILES];
		int PlayerCount;
		bool Created = false;
		sf::Text CreatedProfile;
		bool TooManyPlayers = false;
		sf::Text TooMany;

		sf::Sprite Outline;
		sf::Sprite Arrows;
		sf::Text MoveGuide;
		sf::Sprite Trash;

		sf::String PlayerInput;
		sf::Text CreateNew;
	};
}