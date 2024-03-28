#include "ExitSave.hpp"
using namespace std;
namespace Bongo
{
	ExitSave::ExitSave(GameDataRef data) : _data(data)
	{
		this->_data->assets.LoadFont("How To Font", FONT_FIXEDSYS_FILEPATH);

		Window.setFillColor(sf::Color(128, 128, 128));
		Window.setSize(sf::Vector2f(600.0f, 400.0f));
		Window.setOutlineColor(sf::Color::White);
		Window.setOutlineThickness(4);
		Window.setPosition(100.0f, 80.0f);

		DoYou.setFont(this->_data->assets.GetFont("How To Font"));
		DoYou.setFillColor(sf::Color::White);
		DoYou.setPosition(160.0f, 100.f);
		DoYou.setCharacterSize(45);
		DoYou.setString("DO YOU WANT TO LEAVE?");
		DoYou.setOutlineThickness(3);
		DoYou.setOutlineColor(sf::Color::Black);

	}

	void ExitSave::ClearUsed( string filepath)
	{
		ofstream myfile(filepath);
		if (myfile.is_open())
		{
			myfile << "0";

			myfile.close();

			/*cout << "Used Restarted Properly" << endl;*/
		}
		else cout << "Unable to open file" << endl;
	}


	
	
	void ExitSave::Draw()
	{
		this->_data->window.draw(this->Window);
		this->_data->window.draw(this->DoYou);

	}
}