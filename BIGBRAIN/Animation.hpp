#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
namespace Bongo
{
	class Animation
	{
	public:
		Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

		void Update(int row, float deltaTime, bool faceRight);

		sf::IntRect uvRect;

	private:
		sf::Vector2u imageCount;
		sf::Vector2u currentImage;

		float totalTime;
		float switchTime;
	};
}
