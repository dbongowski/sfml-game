#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.hpp" 
#include "Collider.hpp"
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace Bongo
{
	class Player
	{
	public:

		Player(sf::Texture* texture, float jumpheight, GameDataRef data);

		void Update(float deltaTime);
		void DrawPlayer();
		void OnCollision(sf::Vector2f direction);


		sf::Vector2f GetPosition() { return body.getPosition(); }

		Collider GetCollider() { return Collider(body); }


	private:

		GameDataRef _data;
		sf::RectangleShape body;
		unsigned int row;
		float speed;
		bool faceRight;
		sf::Vector2f velocity;
		float jumpHeight;
		bool canjump = true;

		Animation* animation;
	};
}
