#pragma once

#include <sstream>
#include "DEFINITIONS.hpp"
#include "PenguinState.hpp"
#include "MainMenuState.hpp"
#include "Collider.hpp"

Bongo::PenguinState::PenguinState(GameDataRef data) : _data(data)
{
}

void Bongo::PenguinState::Init()
{
	this->_data->assets.LoadTexture("Floor Penguin Texture", FLOOR_PENGUIN_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("Diamond Texture", BLOCK_DIAMOND_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("Penguin Texture", PENGUIN_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("Save And Exit", SAVE_N_EXIT_FILEPATH);
	this->_data->assets.LoadTexture("Dont Save And Exit", DONT_SAVE_N_EXIT_FILEPATH);
	this->_data->assets.LoadTexture("Return", RETURN_FILEPATH);


	LoadProfiles();

	exitsave = new ExitSave(_data);
	floor = new StartBackground(&this->_data->assets.GetTexture("Floor Penguin Texture"), sf::Vector2f(800.0f, 100.0f), sf::Vector2f(360.0f, -40.0f), sf::Vector2f(360.0f, 480.0f), _data);
	wallL = new StartBackground(nullptr, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(50.0f, 0.0f), sf::Vector2f(-85.0f, 0.0f), _data);
	wallR = new StartBackground(nullptr, sf::Vector2f(100.0f, 700.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(805.0f, 0.0f), _data);
	block1 = new Block(&this->_data->assets.GetTexture("Diamond Texture"), sf::Vector2f(165.0f, 100.0f), sf::Vector2f(35.0f, -60.0f), sf::Vector2f(53.0f, 100.0f), _data);
	block2 = new Block(&this->_data->assets.GetTexture("Diamond Texture"), sf::Vector2f(165.0f, 100.0f), sf::Vector2f(35.0f, -60.0f), sf::Vector2f(253.0f, 100.0f), _data);
	block3 = new Block(&this->_data->assets.GetTexture("Diamond Texture"), sf::Vector2f(165.0f, 100.0f), sf::Vector2f(35.0f, -60.0f), sf::Vector2f(453.0f, 100.0f), _data);
	block4 = new Block(&this->_data->assets.GetTexture("Diamond Texture"), sf::Vector2f(165.0f, 100.0f), sf::Vector2f(35.0f, -60.0f), sf::Vector2f(653.0f, 100.0f), _data);
	player = new Player(&this->_data->assets.GetTexture("Penguin Texture"), 170.0f, _data);
	text = new TextPenguin(25, 0, PlayerNumber, PlayerNames[PlayerNumber], _data);
	F1howto = new F1HowTo(_data);
	LoadBlockNums();
	LoadPairNums();

	PointsFrame.setFillColor(sf::Color::White);
	PointsFrame.setOutlineColor(sf::Color::Black);
	PointsFrame.setOutlineThickness(3);
	PointsFrame.setPointCount(6);
	PointsFrame.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	PointsFrame.setPoint(1, sf::Vector2f(75.0f, 0.0f));
	PointsFrame.setPoint(2, sf::Vector2f(95.0f, -25.0f));
	PointsFrame.setPoint(3, sf::Vector2f(75.0f, -50.0f));
	PointsFrame.setPoint(4, sf::Vector2f(0.0f, -50.0f));
	PointsFrame.setPoint(5, sf::Vector2f(-20.0f, -25.0f));
	PointsFrame.setPosition(705.0f, 75.0f);

}

void Bongo::PenguinState::HandleInput()
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
				ShowExit = !ShowExit;
				if (ShowExit == true)
				{
					for (int i = 0; i < 3; i++)
					{
						Exit[i].setTexture(this->_data->assets.GetTexture(Filepath[i]));
						Exit[i].setPosition(position[2 * i], position[(2 * i) + 1]);
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						Exit[i].setTexture(this->_data->assets.GetTexture(Filepath[i]));
						Exit[i].setPosition(positionOUT[2 * i], positionOUT[(2 * i) + 1]);
					}
				}
				/*this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);*/
			}
			else if (event.key.code == sf::Keyboard::F1)
			{
				ShowF1HowTo = !ShowF1HowTo;
				ShowPressF1 = false;
			}
		}
		if (_data->input.IsSpriteClicked(Exit[0], sf::Mouse::Left, _data->window))
		{
			text->SaveUsed();
			this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
		}

		else if (_data->input.IsSpriteClicked(Exit[1], sf::Mouse::Left, _data->window))
		{
			text->UsedRestart();
			exitsave->ClearUsed(USED_INDEX_PENGUIN_TXT_FILEPATH);
			this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
		}
		else if (_data->input.IsSpriteClicked(Exit[2], sf::Mouse::Left, _data->window))
		{
			ShowExit = false;
		}
	}
}

void Bongo::PenguinState::Update(float dt)
{
		if (UsedIndex == (NUMBER_OF_QUESTIONS - 2))
			ShowEND = true;

		if (ShowEND == true)
		{
			if (this->_clock.getElapsedTime().asSeconds() > END_SHOW_TIME)
			{
				text->UsedRestart();
				exitsave->ClearUsed(USED_INDEX_PENGUIN_TXT_FILEPATH);
				this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
			}
		}

		if (ShowEND == false)
			_clock.restart();

		player->Update(dt);

		if (ShowF1HowTo == true)
			F1howto->Update(dt);

		sf::Vector2f direction;
		Collider playerCollision = player->GetCollider();

		if (floor->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
			player->OnCollision(direction);
		if (wallL->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
			player->OnCollision(direction);
		if (wallR->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
			player->OnCollision(direction);
		if (block1->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
		{
			player->OnCollision(direction);
			cout << "Collided block1" << endl;
			ShowCorrect = false;
			ShowPressF1 = false;
			SelectedBlock[SelectCount] = 1;
			UsedIndex = text->ReturnUsedIndex();
			SelectCount++;
			if (SelectCount == NUMBER_OF_SELECTIONS)
			{
				CheckCorrect();
				text->SaveUsed();
				text->~TextPenguin();
				text = new TextPenguin(25, UsedIndex, PlayerNumber, PlayerNames[PlayerNumber], _data);
				LoadBlockNums();
				LoadPairNums();

				SelectCount = 0;
			}
		}
		if (block2->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
		{
			player->OnCollision(direction);
			cout << "Collided block2" << endl;
			ShowCorrect = false;
			ShowPressF1 = false;
			SelectedBlock[SelectCount] = 2;
			UsedIndex = text->ReturnUsedIndex();
			SelectCount++;
			if (SelectCount == NUMBER_OF_SELECTIONS)
			{
				CheckCorrect();
				text->SaveUsed();
				text->~TextPenguin();
				text = new TextPenguin(25, UsedIndex, PlayerNumber, PlayerNames[PlayerNumber], _data);
				LoadBlockNums();
				LoadPairNums();

				SelectCount = 0;
			}
		}
		if (block3->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
		{
			player->OnCollision(direction);
			cout << "Collided block3" << endl;
			ShowCorrect = false;
			ShowPressF1 = false;
			SelectedBlock[SelectCount] = 3;
			UsedIndex = text->ReturnUsedIndex();
			SelectCount++;
			if (SelectCount == NUMBER_OF_SELECTIONS)
			{
				CheckCorrect();
				text->SaveUsed();
				text->~TextPenguin();
				text = new TextPenguin(25, UsedIndex, PlayerNumber, PlayerNames[PlayerNumber], _data);
				LoadBlockNums();
				LoadPairNums();

				SelectCount = 0;
			}
		}
		if (block4->GetCollider().CheckCollision(playerCollision, direction, 1.0f))
		{
			player->OnCollision(direction);
			cout << "Collided block4" << endl;
			ShowCorrect = false;
			ShowPressF1 = false;
			UsedIndex = text->ReturnUsedIndex();
			SelectedBlock[SelectCount] = 4;
			SelectCount++;
			if (SelectCount == NUMBER_OF_SELECTIONS)
			{
				CheckCorrect();
				text->SaveUsed();
				text->~TextPenguin();
				text = new TextPenguin(25, UsedIndex, PlayerNumber, PlayerNames[PlayerNumber], _data);
				LoadBlockNums();
				LoadPairNums();

				SelectCount = 0;
			}
		}

}

void Bongo::PenguinState::Draw(float dt)
{


	this->_data->window.clear(sf::Color(153, 235, 255));

	wallL->DrawBackground();
	wallR->DrawBackground();
	floor->DrawBackground();
	block1->DrawBlock();
	block2->DrawBlock();
	block3->DrawBlock();
	block4->DrawBlock();
	player->DrawPlayer();
	this->_data->window.draw(this->PointsFrame);
	text->DrawText();
	if (ShowCorrect == true)
	{
		text->DrawCorrect(correct);
	}
	if (ShowF1HowTo == true)
		F1howto->DrawHowTo();
	if (ShowPressF1 == true)
		text->DrawHowTo();
	if (ShowEND == true)
		text->DrawEND();
	if (ShowExit == true)
	{
		exitsave->Draw();
		for (int i = 0; i < 3; i++)
		{
			this->_data->window.draw(this->Exit[i]);
		}
	}

	this->_data->window.display();
}


void Bongo::PenguinState::CheckCorrect()
{

	if ((SelectedBlock[0] == Pair1Check[0] || SelectedBlock[1] == Pair1Check[0]) && (SelectedBlock[0] == Pair1Check[1] || SelectedBlock[1] == Pair1Check[1]))
	{
		cout << "Correct Answer!!!" << endl;
		correct = true;
		PlayerPoints[PlayerNumber]++;
		SavePoints();
	}
	else if ((SelectedBlock[0] == Pair2Check[0] || SelectedBlock[1] == Pair2Check[0]) && (SelectedBlock[0] == Pair2Check[1] || SelectedBlock[1] == Pair2Check[1]))
	{
		cout << "Correct Answer!!!" << endl;
		correct = true;
		PlayerPoints[PlayerNumber]++;
		SavePoints();
	}
	else
	{
		cout << "Incorrect Answer" << endl;
		correct = false;
	}
	ShowCorrect = true;
}


void Bongo::PenguinState::LoadBlockNums()
{
	ifstream File;
	File.open(BLOCK_NUMS_TXT_FILEPATH);

	int n = 0;

	while (!File.eof())
	{
		File >> BlockNums[n];
		n++;
	}

	File.close();

	for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
	{
		cout << "BlockNums[" << i + 1 << "] = " << BlockNums[i] << endl;
	}
}

void Bongo::PenguinState::LoadPairNums()
{
	ifstream File1;
	File1.open(PAIR1_TXT_FILEPATH);

	int n = 0;

	while (!File1.eof())
	{
		File1 >> Pair1Check[n];
		n++;
	}

	File1.close();

	ifstream File2;
	File2.open(PAIR2_TXT_FILEPATH);

	n = 0;

	while (!File2.eof())
	{
		File2 >> Pair2Check[n];
		n++;
	}

	File2.close();

	for (int i = 0; i < 2; i++)
	{
		cout << "Pair1[" << i << "] = " << Pair1Check[i] << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		cout << "Pair2[" << i << "] = " << Pair2Check[i] << endl;
	}
}

void Bongo::PenguinState::SavePoints()
{
	ofstream myfile(PROFILES_POINTS_TXT_FILEPATH);
	if (myfile.is_open())
	{
		for (int i = 0; i <= PlayerCount; i++)
		{
			myfile << PlayerPoints[i] << endl;
		}
		myfile.close();
		//cout << "Points Saved properly" << endl;
	}
	else cout << "Unable to open file" << endl;
}

void Bongo::PenguinState::LoadProfiles()
{
		int n = 0;

		ifstream File;
		File.open(PROFILES_POINTS_TXT_FILEPATH);

		while (!File.eof())
		{
			File >> PlayerPoints[n];
			n++;
		}

		File.close();

		string line;
		ifstream File1;

		n = 0;

		File1.open(PROFILES_NAMES_TXT_FILEPATH);
		while (getline(File1, line))
		{
			PlayerNames[n] = line;
			PlayerCount++;
			n++;
		}

		n = 0;

		File1.close();

		ifstream File2;
		File2.open(PLAYER_NUMBER_TXT_FILEPATH);

			File2 >> PlayerNumber;

		File2.close();
}
