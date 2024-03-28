#include "ChooseProfileState.hpp"


namespace Bongo
{


    ChooseProfileState::ChooseProfileState(GameDataRef data) : _data(data)
    {
    }
    void ChooseProfileState::Init()
    {


        this->_data->assets.LoadTexture("Choose Profile Background", CHOOSE_PROFILE_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Input Field Texture", INPUT_FIELD_TEXTURE_FILEPATH);
        this->_data->assets.LoadTexture("Arrows Texture", ARROWS_TEXTURE_FILEPATH);
        this->_data->assets.LoadTexture("Arrows Red Texture", ARROWS_RED_TEXTURE_FILEPATH);
        this->_data->assets.LoadFont("Choose Profile Font", FONT_FIXEDSYS_FILEPATH);
        this->_data->assets.LoadTexture("Outline Texture", OUTLINE_TEXTURE_FILEPATH);
        this->_data->assets.LoadTexture("Trash Texture", TRASH_TEXTURE_FILEPATH);
        
        Background.setTexture(this->_data->assets.GetTexture("Choose Profile Background"));

        Outline.setTexture(this->_data->assets.GetTexture("Outline Texture"));
        Outline.setPosition(80.0f, 295.0f);

        Arrows.setTexture(this->_data->assets.GetTexture("Arrows Texture"));
        Arrows.setPosition(730.0f, 30.0f);

        Trash.setTexture(this->_data->assets.GetTexture("Trash Texture"));
        Trash.setPosition(670.0f, 380.0f);

        CreateNew.setFont(this->_data->assets.GetFont("Choose Profile Font"));
        CreateNew.setFillColor(sf::Color::Black);
        CreateNew.setPosition(220.f, 80.f);
        CreateNew.setCharacterSize(40);

        InputField.setTexture(this->_data->assets.GetTexture("Input Field Texture"));
        InputField.setPosition(200.0f, 50.0f);
        
        for (int i = 0; i < MAX_NUMBER_OF_PROFILES + 1; i++)
        {
            ChooseOption[i].setFont(this->_data->assets.GetFont("Choose Profile Font"));
            ChooseOption[i].setCharacterSize(40);
            ChooseOption[i].setFillColor(sf::Color::White);
            ChooseOption[i].setString(ChooseOptionString[i]);
            ChooseOption[i].setPosition(ChoosePosition[2 * i], ChoosePosition[(2 * i) + 1]);
            ChooseOption[i].setOutlineThickness(3);
            ChooseOption[i].setOutlineColor(sf::Color::Black);
        }
       
        ChooseOption[0].setFillColor(sf::Color::Red);

        TooMany.setFont(this->_data->assets.GetFont("Choose Profile Font"));
        TooMany.setFillColor(sf::Color::Red);
        TooMany.setPosition(220.f, 10.f);
        TooMany.setCharacterSize(40);
        TooMany.setString("TOO MANY PLAYERS!!!");
        TooMany.setOutlineThickness(1);
        TooMany.setOutlineColor(sf::Color::Black);

        CreatedProfile.setFont(this->_data->assets.GetFont("Choose Profile Font"));
        CreatedProfile.setFillColor(sf::Color::Green);
        CreatedProfile.setPosition(220.f, 10.f);
        CreatedProfile.setCharacterSize(40);
        CreatedProfile.setString("CREATED PROFILE !");
        CreatedProfile.setOutlineThickness(1);
        CreatedProfile.setOutlineColor(sf::Color::Black);

        MoveGuide.setFont(this->_data->assets.GetFont("Choose Profile Font"));
        MoveGuide.setFillColor(sf::Color::Green);
        MoveGuide.setPosition(630.0f, 50.f);
        MoveGuide.setCharacterSize(25);
        MoveGuide.setString("USE\nARROWS\nTO MOVE\nAROUND");
        MoveGuide.setOutlineThickness(1);
        MoveGuide.setOutlineColor(sf::Color::Black);

        for (int i = 0; i < 2; i++)
        {
            AdditionalInfo[i].setFont(this->_data->assets.GetFont("Choose Profile Font"));
            AdditionalInfo[i].setFillColor(sf::Color::Yellow);
            AdditionalInfo[i].setPosition(AdditionalPosition[2 * i], AdditionalPosition[(2 * i) + 1]);
            AdditionalInfo[i].setCharacterSize(32);
            AdditionalInfo[i].setString(AdditionalString[i]);
            AdditionalInfo[i].setOutlineThickness(1);
            AdditionalInfo[i].setOutlineColor(sf::Color::Black);
        }
        selectID = 0;

        LoadProfiles();

    }
    void ChooseProfileState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (_data->input.IsSpriteClicked(Trash, sf::Mouse::Left, _data->window))
            {
                DeleteProfile();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    if (PlayerInput.getSize() != NULL)
                    {
                        PlayerInput.erase((PlayerInput.getSize() - 1), 1);
                        CreateNew.setString(PlayerInput);
                    }
                }
                else
                {
                    PlayerInput += static_cast<char>(event.text.unicode);
                    CreateNew.setString(PlayerInput);
                }

            }
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

                case sf::Keyboard::Escape:
                    this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
                    break;

                case sf::Keyboard::Enter:
                    switch (selectID)
                    {
                    case 0:
                        if (PlayerCount != 3) 
                        {
                            NewPlayerName = PlayerInput;   
                            PlayerInput.erase((PlayerInput.getSize() - PlayerInput.getSize()), PlayerInput.getSize());
                            playerprofile[PlayerCount] = new PlayerProfile;
                            playerprofile[PlayerCount]->Name = NewPlayerName;
                            playerprofile[PlayerCount]->Points = 0;
                            cout << "New Player Name = " << playerprofile[PlayerCount]->Name << endl;
                            cout << "New Player Points = " << playerprofile[PlayerCount]->Points << endl;
                            PlayerNames[PlayerCount] = playerprofile[PlayerCount]->Name;
                            PlayerPoints[PlayerCount] = playerprofile[PlayerCount]->Points;
                            ChooseOption[PlayerCount + 1].setString(PlayerNames[PlayerCount]);
                            TooManyPlayers = false;
                            Created = true;
                            PlayerCount++;   
                            SaveProfiles();               
                        }
                        else
                        {
                            Created = false;
                            TooManyPlayers = true;
                        }
                        break;
                    case 1:
                        this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
                        SavePlayerNumber();
                        break;
                    case 2:
                        this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
                        SavePlayerNumber();
                        break;
                    case 3:
                        this->_data->machine.AddState(StateRef(new ChooseLevelState(_data)), true);
                        SavePlayerNumber();
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
    void ChooseProfileState::Update(float dt)
    {
        if (this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_TIME)
        {
            Arrows.setTexture(this->_data->assets.GetTexture("Arrows Texture"));

        }
        else if (this->_clock.getElapsedTime().asSeconds() > INSTRUCTION_ANIMATION_TIME && this->_clock.getElapsedTime().asSeconds() < INSTRUCTION_ANIMATION_RESTART_TIME)
        {
            Arrows.setTexture(this->_data->assets.GetTexture("Arrows Red Texture"));

        }
        else
        {
            _clock.restart();
        }
    }
    void ChooseProfileState::Draw(float dt)
    {
        this->_data->window.clear();
       
        this->_data->window.draw(this->Background);
        this->_data->window.draw(this->InputField);
        this->_data->window.draw(this->CreateNew);

        if (TooManyPlayers == true)
        {
            this->_data->window.draw(this->TooMany);
        }

        if (Created == true)
        {
            this->_data->window.draw(this->CreatedProfile);          
        }

        this->_data->window.draw(this->Outline);

        this->_data->window.draw(this->Arrows);
       
        this->_data->window.draw(this->MoveGuide);

        this->_data->window.draw(this->Trash);

        for (int i = 0; i < MAX_NUMBER_OF_PROFILES + 1; i++)
        {
            this->_data->window.draw(this->ChooseOption[i]);
        }
        for (int i = 0; i < 2; i++)
        {
            this->_data->window.draw(this->AdditionalInfo[i]);
        }


        this->_data->window.display();
    }
    void ChooseProfileState::MoveUp()
    {
        if (selectID - 1 >= 0)
        {
            ChooseOption[selectID].setFillColor(sf::Color::White);
            selectID--;
            ChooseOption[selectID].setFillColor(sf::Color::Red);
        }
    }
    void ChooseProfileState::MoveDown()
    {
        if (selectID + 1 < MAX_NUMBER_OF_PROFILES + 1)
        {
            ChooseOption[selectID].setFillColor(sf::Color::White);
            selectID++;
            ChooseOption[selectID].setFillColor(sf::Color::Red);
        }
 
    }

    void ChooseProfileState::SaveProfiles()
    {
        ofstream myfile(PROFILES_POINTS_TXT_FILEPATH);
        if (myfile.is_open())
        {
            for (int i = 0; i < PlayerCount; i++)
            {
                myfile << PlayerPoints[i] << endl;
            }
            myfile.close();
            //cout << "Profiles Saved properly" << endl;
        }
        else cout << "Unable to open file" << endl;

        ofstream myfile1(PROFILES_NAMES_TXT_FILEPATH);
        if (myfile1.is_open())
        {
            for (int i = 0; i < PlayerCount; i++)
            {
                myfile1 << PlayerNames[i] << endl;
            }
            myfile1.close();
            cout << "Profies Saved properly" << endl;
        }
        else cout << "Unable to open file" << endl;
    }

    void ChooseProfileState::LoadProfiles()
    {
        int n = 0;

        ifstream File1;
        File1.open(PROFILES_POINTS_TXT_FILEPATH);

        while (!File1.eof())
        {
            File1 >> PlayerPoints[n];
            n++;
        }

        File1.close();
    
        string line;
        ifstream File;

        n = 0;

        File.open(PROFILES_NAMES_TXT_FILEPATH);
        while (getline(File, line))
        {
            playerprofile[n] = new PlayerProfile;
            playerprofile[n]->Name = line;
            PlayerNames[n] = playerprofile[n]->Name;
            playerprofile[n]->Points = PlayerPoints[n];
            cout << playerprofile[n]->Points << endl;
            cout << playerprofile[n]->Name << endl;
            if (PlayerNames[n] != "")
            {
                ChooseOption[PlayerCount + 1].setString(playerprofile[n]->Name);             
                PlayerCount++;
            }
            n++;
            cout << "Player " << PlayerCount << " Successfully loaded" << endl;
        }

        File.close();

    }

    void ChooseProfileState::SavePlayerNumber()
    {
        ofstream myfile(PLAYER_NUMBER_TXT_FILEPATH);
        if (myfile.is_open())
        {
                myfile << (selectID - 1) << endl;

            myfile.close();
            //cout << "Profiles Saved properly" << endl;
        }
        else cout << "Unable to open file" << endl;
    }

    void ChooseProfileState::DeleteProfile()
    {
        switch (selectID)
        {
        case 1:
            PlayerPoints[0] = NULL;
            PlayerNames[0] = "";
            SaveProfiles();
            ChooseOption[1].setString("1.");
            if (PlayerCount > 0)       
                PlayerCount--;
            break;
        case 2:
            PlayerPoints[1] = NULL;
            PlayerNames[1] = "";
            SaveProfiles();
            ChooseOption[2].setString("2.");
            if (PlayerCount > 0)
                PlayerCount--;
            break;
        case 3:
            PlayerPoints[2] = NULL;
            PlayerNames[2] = "";
            SaveProfiles();
            ChooseOption[3].setString("3.");
            if (PlayerCount > 0)
                PlayerCount--;
            break;
        }
    }
}
