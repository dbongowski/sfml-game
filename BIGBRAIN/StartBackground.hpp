#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collider.hpp"
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Bongo
{
	class StartBackground
	{
	public:
		StartBackground(sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin, sf::Vector2f position, GameDataRef data);
		void DrawBackground();
		Collider GetCollider() { return  Collider(body); }

	private:
		GameDataRef _data;
		sf::RectangleShape body/*[NUMBER_OF_WALLS]*/;
		float size[NUMBER_OF_WALLS * 2] = { 800, 100, /*100, 700, 100, 700*/ };
		float origin[NUMBER_OF_WALLS * 2] = { 360, -30,/* 0, 0, 0, 0*/ };
		float position[NUMBER_OF_WALLS * 2] = { 360, 480,/* -100, 0, 820, 0*/ };
		//sf::Texture floorT;
		//sf::Sprite floorS;
	};
}
