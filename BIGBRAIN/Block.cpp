#include "Block.hpp"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
namespace Bongo
{
	Block::Block(sf::Texture* texture, sf::Vector2f size, sf::Vector2f origin, sf::Vector2f position, GameDataRef data) : _data(data)
	{
		body.setSize(size);
		body.setOrigin(origin);
		body.setTexture(texture);
		body.setPosition(position);

	}

	void Block::DrawBlock() {

		this->_data->window.draw(this->body);
	}

}