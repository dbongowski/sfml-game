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
	class Block
	{
	public:
		Block(sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin, sf::Vector2f position, GameDataRef data);
		void DrawBlock();
		Collider GetCollider() { return  Collider(body); }

	private:
		GameDataRef _data;
		sf::RectangleShape body;
	};
}
