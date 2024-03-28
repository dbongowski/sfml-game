#include "F1HowTo.hpp"

Bongo::F1HowTo::F1HowTo(GameDataRef data) : _data(data)
{
	this->_data->assets.LoadTexture("How To Arrows", HOW_TO_ARROWS_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("How To WSAD", HOW_TO_WSAD_TEXTURE_FILEPATH);
	this->_data->assets.LoadFont("How To Font", FONT_FIXEDSYS_FILEPATH);

	Arrows.setTexture(this->_data->assets.GetTexture("How To Arrows"));

	Arrows.setPosition(600.0f, 370.0f);

	Instructions.setFont(this->_data->assets.GetFont("How To Font"));
	Instructions.setFillColor(sf::Color::Red);
	Instructions.setPosition(50.f, 250.f);
	Instructions.setCharacterSize(48);
	Instructions.setString("JUMP USING UP OR W, AND SELECT\nCORRECT PAIRS OF ANSWERS BY\nHITTING THEM WITH HEAD");
	Instructions.setOutlineThickness(3);
	Instructions.setOutlineColor(sf::Color::Black);

	Escape.setFont(this->_data->assets.GetFont("How To Font"));
	Escape.setFillColor(sf::Color::Red);
	Escape.setPosition(50.f, 530.f);
	Escape.setCharacterSize(40);
	Escape.setString("PRESS ESCAPE TO EXIT TO MAIN MENU");
	Escape.setOutlineThickness(3);
	Escape.setOutlineColor(sf::Color::Black);

	for (int i = 0; i < 2; i++)
	{
		PointsName[i].setFont(this->_data->assets.GetFont("How To Font"));
		PointsName[i].setCharacterSize(40);
		PointsName[i].setFillColor(sf::Color::Red);
		PointsName[i].setString(PointsNameString[i]);
		PointsName[i].setPosition(position[2 * i], position[(2 * i) + 1]);
		PointsName[i].setOutlineThickness(3);
		PointsName[i].setOutlineColor(sf::Color::Black);
	}
}

void Bongo::F1HowTo::Update(float dt)
{
	if (this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME)
	{
		Arrows.setTexture(this->_data->assets.GetTexture("How To Arrows"));

	}
	else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_RESTART_TIME)
	{
		Arrows.setTexture(this->_data->assets.GetTexture("How To WSAD"));

	}
	else
	{
		_clock.restart();
	}
}

void Bongo::F1HowTo::DrawHowTo()
{

	this->_data->window.draw(this->Arrows);

	this->_data->window.draw(this->Instructions);

	for (int i = 0; i < 2; i++)
		this->_data->window.draw(this->PointsName[i]);

	this->_data->window.draw(this->Escape);


}
