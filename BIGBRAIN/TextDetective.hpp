#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

using namespace std;
namespace Bongo
{
	class TextDetective
	{
	public:
		TextDetective(int size, int UsedIndex, int PlayerNumber, string PlayerName, GameDataRef data);
		~TextDetective();
		void LoadText();
		void texttest();
		void AssignText();
		void Shuffle();
		string TextWrapping(string str, int length);
		void SaveUsed();
		void LoadUsed();
		void UsedRestart();
		void SaveBlockNums();
		void ClearBlockNums();
		void SavePairNums();

		void LoadPoints();

		int ReturnUsedIndex();

		void DrawText();
		void DrawCorrect(bool correct);
		void DrawHowTo();
		void DrawEND();

	private:
		GameDataRef _data;
		sf::Text text[NUMBER_OF_BLOCKS];
		sf::Text Correct[2];
		sf::Text PlayerData[2];
		sf::Text PressF1;
		sf::Text END;
		string CorrectString[2] = { "CORRECT!!!", "INCORRECT!!!" };
		string First[NUMBER_OF_QUESTIONS], Second[NUMBER_OF_QUESTIONS];
		string PointsString;
		string PlayerName;
		int i, nums[NUMBER_OF_BLOCKS] = { 0 }, temp, N = 0, good = 0;
		bool error;
		float position[NUMBER_OF_BLOCKS * 2] = { 20, 170, 220, 170, 420, 170, 620, 170 };
		float PlayerDataPosition[4] = { 710, 15, 20, 15 };
		int Pair[2];
		int UsedArray[NUMBER_OF_QUESTIONS], UsedIndex;
		int PlayerPoints[3], PlayerNumber;

	};
}
