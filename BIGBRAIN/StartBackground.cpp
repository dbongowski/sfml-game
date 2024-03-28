#include "StartBackground.hpp"
#include <iostream>

using namespace std;

namespace Bongo
{
	StartBackground::StartBackground(sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin, sf::Vector2f position, GameDataRef data) : _data(data)
	{
		this->_data->assets.LoadTexture("Floor Texture", FLOOR1_TEXTURE_FILEPATH);
		
		body.setSize(size);
		body.setOrigin(origin);
		body.setTexture(texture);
		body.setPosition(position);



		//for (int i = 0; i < NUMBER_OF_WALLS; i++)
		//{
		//	body/*[i]*/.setSize(sf::Vector2f(size[2 * i], size[(2 * i) + 1]));
		//	body/*[i]*/.setOrigin(sf::Vector2f(origin[2 * i], origin[(2 * i) + 1]));
		//	body/*[i]*/.setPosition(sf::Vector2f(position[2 * i], position[(2 * i) + 1]));
		//}


		//body/*[0]*/.setTexture(&this->_data->assets.GetTexture("Floor Texture"));
	}

	void StartBackground::DrawBackground() 
	{
		for (int i = 0; i < NUMBER_OF_WALLS; i++)
		{
			this->_data->window.draw(this->body/*[i]*/);
		}

	}
}