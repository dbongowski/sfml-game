#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

using namespace std;
namespace Bongo
{
	class ExitSave
	{
	public:
		ExitSave(GameDataRef data);

		void SaveUsed(int UsedIndex, string filepath);
		void ClearUsed(string filepath);

		int ReturnUsed(string filepath);

		void Draw();

	private:
		GameDataRef _data;

		sf::RectangleShape Window;
		sf::Text DoYou;
	};
}
