#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>
#include "StartBackground.hpp"
#include "Player.hpp"
#include "Block.hpp"
#include "TextDetective.hpp"
#include "F1HowTo.hpp"
#include "ChooseLevelState.hpp"
#include "ExitSave.hpp"

namespace Bongo
{
	class DetectiveState : public State
	{
	public:

		DetectiveState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

		void CheckCorrect();
		void LoadBlockNums();
		void LoadPairNums();
		void SavePoints();


		void LoadProfiles();

	private:

		GameDataRef _data;
		sf::Clock _clock;

		sf::ConvexShape PointsFrame;

		StartBackground *floor;
		Player* player;
		StartBackground *wallL;
		StartBackground *wallR;
		Block* block1;
		Block* block2;
		Block* block3;
		Block* block4;
		TextDetective* text;
		F1HowTo* F1howto;
		ExitSave* exitsave;

		int SelectedBlock[NUMBER_OF_SELECTIONS];
		int SelectCount;
		int UsedArray[NUMBER_OF_QUESTIONS], UsedIndex;
		int BlockNums[NUMBER_OF_BLOCKS];

		int Pair1Check[2];
		int Pair2Check[2];

		sf::Sprite Background;

		string PlayerNames[MAX_NUMBER_OF_PROFILES];
		int PlayerPoints[MAX_NUMBER_OF_PROFILES];
		int PlayerNumber, PlayerCount;

		sf::Text PlayerProfile[2];

		sf::Sprite Exit[3];
		string Filepath[3] = { "Save And Exit" , "Dont Save And Exit" , "Return" };
		float position[6] = { 160, 200, 160, 300, 160, 400 };
		float positionOUT[6] = { 1000,1000,1000,1000,1000,1000 };

		bool correct;
		bool ShowCorrect = false;
		bool ShowF1HowTo = false;
		bool ShowPressF1 = true;
		bool ShowEND = false;
		bool ShowExit = false;
	};
}
