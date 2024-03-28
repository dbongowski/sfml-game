#include "Player.hpp"

#include <iostream>

using namespace std;

namespace Bongo
{
	Player::Player(sf::Texture* texture, float jumpheight, GameDataRef data) : _data(data)
	{


		animation = new Animation(texture, sf::Vector2u(3, 9), 0.3f);
		speed = 250;
		this->jumpHeight = jumpheight;
		row = 0;
		faceRight = true;

		body.setSize(sf::Vector2f(80.0f, 170.0f));
		body.setPosition(200.0f, 350.0f);
		body.setTexture(texture);
	}

	void Player::Update(float deltaTime)
	{
		velocity.x = 0.0f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocity.x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocity.x += speed;
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canjump) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canjump)) //only when canJump = true
		{
			canjump = false;

			velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); // square root (2.0f * gravity * jumpHeight)
		}


		velocity.y += 981.0f * deltaTime;

		if (velocity.x == 0.0f)
		{
			row = 0;
		}
		else
		{
			row = 1;
			if (velocity.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
		}
	
		animation->Update(row, deltaTime, faceRight);
		body.setTextureRect(animation->uvRect);
		body.move(velocity * deltaTime);
	}

	void Player::OnCollision(sf::Vector2f direction)
	{
		if (direction.x < 0.0f)
		{
			velocity.x = 0.0f; //collision on the left
		}
		else if (direction.x > 0.0f)
		{
			velocity.x = 0.0f; //collision on the right
		}
		if (direction.y < 0.0f)
		{
			velocity.y = 0.0f; // collision on the bottom
			canjump = true;
		}
		else if (direction.y > 0.0f)
		{
			velocity.y = 0.0f; //collision on the top

		}
	}

	void Player::DrawPlayer()
	{
		this->_data->window.draw(this->body);
	}
}

