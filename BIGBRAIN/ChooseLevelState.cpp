#include "ChooseLevelState.hpp"

Bongo::ChooseLevelState::ChooseLevelState(GameDataRef data) : _data(data)
{
}

void Bongo::ChooseLevelState::Init()
{
	//textdetective = new TextDetective(25, 0, 0, "", _data);
	//textpenguin = new TextPenguin(25, 0, 0, "", _data);
	//textmusic = new TextMusic(25, 0, 0, "", _data);

	//textdetective->UsedRestart();
	//textpenguin->UsedRestart();
	//textmusic->UsedRestart();

	this->_data->assets.LoadTexture("Choose Level Background", CHOOSE_LEVEL_BACKGROUND_FILEPATH);
	this->_data->assets.LoadTexture("Detective Level Texture", DETECTIVE_LEVEL_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("Penguin Level Texture", PENGUIN_LEVEL_TEXTURE_FILEPATH);
	this->_data->assets.LoadTexture("Music Level Texture", MUSIC_LEVEL_TEXTURE_FILEPATH);

	this->_data->assets.LoadFont("Choose Level Font", FONT_FIXEDSYS_FILEPATH);

	Background.setTexture(this->_data->assets.GetTexture("Choose Level Background"));

	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		Level[i].setTexture(this->_data->assets.GetTexture(TextureName[i]));
		Level[i].setPosition(IconPosition[2 * i], IconPosition[(2 * i) + 1]);
	}
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		LevelName[i].setFont(this->_data->assets.GetFont("Choose Level Font"));
		LevelName[i].setFillColor(sf::Color::White);
		LevelName[i].setPosition(LevelNamePosition[2 * i], LevelNamePosition[(2 * i) + 1]);
		LevelName[i].setCharacterSize(32);
		LevelName[i].setString(LevelNameString[i]);
		LevelName[i].setOutlineThickness(1);
		LevelName[i].setOutlineColor(sf::Color::Black);
	}

	Instruction.setFont(this->_data->assets.GetFont("Choose Level Font"));
	Instruction.setPosition(170.f, 50.f);
	Instruction.setString("CLICK ICONS TO CHOOSE LEVELS");
	Instruction.setOutlineColor(sf::Color::Black);
	Instruction.setCharacterSize(35);
	Instruction.setFillColor(sf::Color::White);
	Instruction.setOutlineThickness(3);
}

void Bongo::ChooseLevelState::HandleInput()
{

	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			this->_data->window.close();

		if (_data->input.IsSpriteClicked(Level[0], sf::Mouse::Left, _data->window))
			this->_data->machine.AddState(StateRef(new PenguinState(_data)), true);
		else if (_data->input.IsSpriteClicked(Level[1], sf::Mouse::Left, _data->window))
			this->_data->machine.AddState(StateRef(new DetectiveState(_data)), true);
		else if (_data->input.IsSpriteClicked(Level[2], sf::Mouse::Left, _data->window))
			this->_data->machine.AddState(StateRef(new MusicState(_data)), true);

		if (sf::Event::KeyPressed == event.type)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->_data->machine.AddState(StateRef(new ChooseProfileState(_data)), true);
			}
		}
	}
}

void Bongo::ChooseLevelState::Update(float dt)
{	
	if (this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME)
	{
		Instruction.setCharacterSize(37);
		Instruction.setFillColor(sf::Color::White);
		Instruction.setOutlineThickness(3);
		Instruction.setPosition(156.f, 30.f);
	}
	else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_RESTART_TIME)
	{
		Instruction.setCharacterSize(40);
		Instruction.setFillColor(sf::Color(255, 255, 102));
		Instruction.setOutlineThickness(1);
		Instruction.setPosition(133.f, 30.f);
	}
	else
	{
		_clock.restart();
	}

}

void Bongo::ChooseLevelState::Draw(float dt)
{
	this->_data->window.clear();

	this->_data->window.draw(this->Background);

	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		this->_data->window.draw(this->Level[i]);
	}
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		this->_data->window.draw(this->LevelName[i]);
	}

	this->_data->window.draw(this->Instruction);

	this->_data->window.display();
}
