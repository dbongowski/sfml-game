#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"

using namespace std;
namespace Bongo
{

	class F1HowTo
	{
	public:

		F1HowTo(GameDataRef data);
		void Update(float dt);

		void DrawHowTo();

	private:
		GameDataRef _data;

		sf::Text Instructions;
		sf::Text PointsName[2];
		sf::Text Escape;
		sf::Sprite Arrows;

		string PointsNameString[2] = { "YOUR POINTS->", "<-YOUR NAME" };
		float position[4] = { 450, 30, 200, 30 };

		sf::Clock _clock;
	};
}
