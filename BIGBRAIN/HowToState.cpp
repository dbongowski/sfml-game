#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "HowToState.hpp"
#include "MainMenuState.hpp"

namespace Bongo
{

	HowToState::HowToState(GameDataRef data) : _data(data)
	{
	}

	void Bongo::HowToState::Init()
	{
		
		this->_data->assets.LoadFont("Main Menu Font", FONT_FIXEDSYS_FILEPATH);
		this->_data->assets.LoadTexture("How1", HOW_TO_PLAY_SCENE_1);
		this->_data->assets.LoadTexture("How2", HOW_TO_PLAY_SCENE_2);
		this->_data->assets.LoadTexture("How3", HOW_TO_PLAY_SCENE_3);
		this->_data->assets.LoadTexture("How4", HOW_TO_PLAY_SCENE_4);
		this->_data->assets.LoadTexture("How5", HOW_TO_PLAY_SCENE_5);

		animation.setTexture(this->_data->assets.GetTexture("How1"));

		exit.setFont(this->_data->assets.GetFont("Main Menu Font"));
		exit.setCharacterSize(36);
		exit.setString("Press Escape To Return To Main Menu");
		exit.setPosition(150.0f, 550.0f);
		exit.setFillColor(sf::Color::Red);
		exit.setOutlineThickness(3);
		exit.setOutlineColor(sf::Color::Black);
	}

	void Bongo::HowToState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (sf::Event::KeyPressed == event.type)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
				}
			}


		}
	}

	void Bongo::HowToState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME)
		{
			animation.setTexture(this->_data->assets.GetTexture("How1"));
		}
		else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME * 2)
		{
			animation.setTexture(this->_data->assets.GetTexture("How2"));
		}
		else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME * 2 && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME * 3)
		{
			animation.setTexture(this->_data->assets.GetTexture("How3"));
		}
		else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME * 3 && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME * 4)
		{
			animation.setTexture(this->_data->assets.GetTexture("How4"));
		}
		else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME * 4 && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME * 5)
		{
			animation.setTexture(this->_data->assets.GetTexture("How5"));
		}
		else
		{
			_clock.restart();
		}
	}

	void Bongo::HowToState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(this->animation);

		this->_data->window.draw(this->exit);

		this->_data->window.display();
	}

}