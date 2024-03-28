#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "HowToState.hpp"
#include "DetectiveState.hpp"
#include "PenguinState.hpp"
#include "ChooseProfileState.hpp"


namespace Bongo
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		std::string text[MAX_NUMBER_OF_OPTIONS] = { "START","HOW TO PLAY","EXIT" };

		this->_data->assets.LoadTexture("Main Menu Logo", MAIN_MENU_LOGO_FILEPATH);
		this->_data->assets.LoadFont("Main Menu Font", FONT_FIXEDSYS_FILEPATH);

		logo.setTexture(this->_data->assets.GetTexture("Main Menu Logo"));
		logo.setPosition(240.f, 10.f);
		credits.setFont(this->_data->assets.GetFont("Main Menu Font"));
		credits.setFillColor(sf::Color::White);
		credits.setString("Image from: https://inspirationalperspective.com \nConverted with: https://img8bit.com");
		credits.setCharacterSize(9);
		credits.setPosition(500.f, 535.f);
		
		for (int i=0; i < MAX_NUMBER_OF_OPTIONS; i++) {
			menu[i].setFont(this->_data->assets.GetFont("Main Menu Font"));
			menu[i].setCharacterSize(70);
			menu[i].setFillColor(sf::Color::White);
			menu[i].setString(text[i]);
			menu[i].setPosition(MenuPosition[2 * i], MenuPosition[(2 * i) + 1]);
		}
		menu[0].setFillColor(sf::Color(230, 115, 0));

		selectID = 0;

		for (int i = 0; i < NUMBER_OF_RIMS; i++)
		{
			obwod[i].setFillColor(sf::Color::Black);
			obwod[i].setOutlineThickness(outline[i]);
			obwod[i].setSize(sf::Vector2f(RimsSize[2 * i], RimsSize[(2 * i) + 1]));
			obwod[i].setPosition(RimsPosition[2 * i], RimsPosition[(2 * i) + 1]);
			obwod[i].setOutlineColor(sf::Color(RimsColor[3 * i], RimsColor[(3 * i) + 1], RimsColor[(3 * i) + 2]));
		}

	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					break;

				case sf::Keyboard::W:
					MoveUp();
					break;

				case sf::Keyboard::S:
					MoveDown();
					break;

				case sf::Keyboard::Enter:
					switch (selectID)
					{
					case 0:
						std::cout << "Start button has been pressed" << std::endl;
						this->_data->machine.RemoveState();
				/*		this->_data->machine.AddState(StateRef(new PenguinState(_data)), true);*/
						this->_data->machine.AddState(StateRef(new ChooseProfileState(_data)), true);
						break;
					case 1:
						std::cout << "How To Play button has been pressed" << std::endl;
						this->_data->machine.RemoveState();
						this->_data->machine.AddState(StateRef(new HowToState(_data)), true);
						break;
					case 2:
						this->_data->window.close();
						std::cout << "Exit button has been pressed" << std::endl;
						break;
					}
				}

				break;
			case sf::Event::Closed:
				this->_data->window.close();
				break;
			}
		}
	}


	void MainMenuState::Update(float dt)
	{
		
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();
		for (int i = 0; i < NUMBER_OF_RIMS; i++)
		{
			this->_data->window.draw(this->obwod[i]);
		}

		this->_data->window.draw(this->logo);

		for (int i = 0; i < MAX_NUMBER_OF_OPTIONS; i++)
		{
			this->_data->window.draw(this->menu[i]);
		}

		this->_data->window.draw(this->credits);

		this->_data->window.display();
	}

	void MainMenuState::MoveUp()
	{
		if (selectID - 1 >= 0)
		{
			menu[selectID].setFillColor(sf::Color::White);
			selectID--;
			menu[selectID].setFillColor(sf::Color(230, 115, 0));
		}
	}

	void MainMenuState::MoveDown()
	{
		if (selectID + 1 < MAX_NUMBER_OF_OPTIONS)
		{
			menu[selectID].setFillColor(sf::Color::White);
			selectID++;
			menu[selectID].setFillColor(sf::Color(230, 115, 0));
		}
	}


}

