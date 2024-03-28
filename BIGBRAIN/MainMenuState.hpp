#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>

namespace Bongo
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void MoveUp();
		void MoveDown();

	private:
		GameDataRef _data;

		sf::Sprite logo;
		sf::Text credits;
		sf::Text menu[MAX_NUMBER_OF_OPTIONS];
		sf::Sprite ClickMenu[MAX_NUMBER_OF_OPTIONS];
		sf::RectangleShape obwod[NUMBER_OF_RIMS];

		int selectID;

		int outline[NUMBER_OF_RIMS] = { 8,5,2 };
		float MenuPosition[2 * NUMBER_OF_RIMS] = { 320, 280, 215, 365, 333, 450 };
		float RimsSize[2 * NUMBER_OF_RIMS] = { 700, 300, 681, 281, 673, 273 };
		float RimsPosition[2 * NUMBER_OF_RIMS] = { 50, 270, 60, 280, 64, 284 };
		int RimsColor[3 * NUMBER_OF_RIMS] = { 0, 0, 128, 153, 38, 0, 128, 32, 0 };
	};
}