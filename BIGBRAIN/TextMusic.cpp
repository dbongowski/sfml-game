#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "TextMusic.hpp"

namespace Bongo
{
	TextMusic::TextMusic(int size, int UsedIndex, int PlayerNumber, string PlayerName, GameDataRef data) : _data(data)
	{
		this->_data->assets.LoadFont("Question Font", FONT_NEW_ROCKER_FILEPATH);

		LoadText();
		LoadUsed();
		LoadPoints();

		this->PlayerNumber = PlayerNumber;

		for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
		{
			text[i].setFont(this->_data->assets.GetFont("Question Font"));
			text[i].setFillColor(sf::Color::White);
			text[i].setPosition(position[2 * i], position[(2 * i) + 1]);
			text[i].setCharacterSize(size);
		}

		for (int i = 0; i < 2; i++)
		{
			Correct[i].setFont(this->_data->assets.GetFont("Question Font"));
			Correct[i].setString(CorrectString[i]);
			Correct[i].setPosition(280.0f, 50.0f);
			Correct[i].setCharacterSize(48);
		}
		Correct[0].setFillColor(sf::Color::Green);
		Correct[1].setFillColor(sf::Color::Red);

		PointsString = to_string(PlayerPoints[PlayerNumber]);

		for (int i = 0; i < 2; i++)
		{
			PlayerData[i].setFont(this->_data->assets.GetFont("Question Font"));
			PlayerData[i].setPosition(PlayerDataPosition[2 * i], PlayerDataPosition[(2 * i) + 1]);
			PlayerData[i].setCharacterSize(48);
			PlayerData[i].setFillColor(sf::Color::Green);
		}
		PlayerData[0].setString(PointsString);
		PlayerData[1].setString(PlayerName);

		PressF1.setFont(this->_data->assets.GetFont("Question Font"));
		PressF1.setFillColor(sf::Color::Red);
		PressF1.setPosition(50.f, 525.0f);
		PressF1.setCharacterSize(40);
		PressF1.setString("PRESS F1 FOR HELP");
		PressF1.setOutlineThickness(3);
		PressF1.setOutlineColor(sf::Color::Black);

		END.setFont(this->_data->assets.GetFont("Question Font"));
		END.setFillColor(sf::Color::Red);
		END.setPosition(100.0f, 280.0f);
		END.setCharacterSize(60);
		END.setString("END OF QUESTIONS");
		END.setOutlineThickness(5);
		END.setOutlineColor(sf::Color::Black);

		//texttest();
		Shuffle();
		AssignText();
		SavePairNums();


	}
	TextMusic::~TextMusic()
	{
	}
	void Bongo::TextMusic::LoadText()
	{
		int i = 0;
		string line;
		ifstream firstFileout, secondFileout;

		firstFileout.open(FIRST_MUSIC_TXT_FILEPATH);
		while (getline(firstFileout, line))
		{
			First[i] = line;
			First[i] = TextWrapping(First[i], 13);
			i++;
		}

		secondFileout.open(SECOND_MUSIC_TXT_FILEPATH);
		i = 0;
		while (getline(secondFileout, line))
		{
			Second[i] = line;
			Second[i] = TextWrapping(Second[i], 13);
			i++;
		}
	}

	void Bongo::TextMusic::texttest()
	{
		for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
		{
			cout << "First[" << i << "] = " << First[i] << endl;
			cout << "Second[" << i << "] = " << Second[i] << endl;
		}
	}

	void Bongo::TextMusic::AssignText()
	{
	
		text[nums[0] - 1].setString(First[Pair[0]]);  //blok 1
		cout << "Blok nr 1 wylosowal numer " << nums[0] << " Zawiera PIERWSZA czesc Pary nr 1 z pytaniem numer " << Pair[0] << endl;
		text[nums[1] - 1].setString(Second[Pair[0]]); //blok 2
		cout << "Blok nr 2 wylosowal numer " << nums[1] << " Zawiera DRUGA czesc Pary nr 1 z pytaniem numer " << Pair[0] << endl;
		text[nums[2] - 1].setString(First[Pair[1]]);  //blok 3
		cout << "Blok nr 3 wylosowal numer " << nums[2] << " Zawiera PIERWSZA czesc Pary nr 2 z pytaniem numer " << Pair[1] << endl;
		text[nums[3] - 1].setString(Second[Pair[1]]); //blok 4
		cout << "Blok nr 4 wylosowal numer " << nums[3] << " Zawiera DRUGA czesc Pary nr 2 z pytaniem numer " << Pair[1] << endl;

	}


	void Bongo::TextMusic::Shuffle()
	{
		//Shuffling blocks

		ClearBlockNums();

		cout << " UsedIndex = " << UsedIndex << endl;

		srand(time(NULL));
		do
		{
			do
			{
				temp = rand() % NUMBER_OF_BLOCKS + 1;
				//cout << "los = " << temp << endl;
				error = false;
				for (i = 0; i < NUMBER_OF_BLOCKS; i++)
				{
					if (nums[i] == temp) //Sprawdz czy nie powtarzaja sie
					{
						error = true;
						//cout << "Istnieje juz taki los dla BLOKOW" << endl;
					}
				}
			} while (error == true);

			good = temp;
			//cout << "OK! wylosowano: " << good << " dla blokow" << endl;

			nums[N] = good;
			//cout << "Wprowadzono Blok nr. " << N + 1 << endl << endl;
			N++;
			
		} while (nums[NUMBER_OF_BLOCKS - 1] == 0);

		for (i = 0; i < 4; i++)
		{
			cout << "Blok Numer " << i + 1 << " wylosowal numer " << nums[i] << endl;
		}

		SaveBlockNums();

		cout << endl;

		//Choosing number of question

		N = 0;

		do
		{
			do
			{
				temp = rand() % NUMBER_OF_QUESTIONS + 0;
				//cout << "los pytania = " << temp << endl;
				error = false;
				for (i = 0; i < 2; i++)
				{
					if (Pair[i] == temp) //Sprawdz czy pary nie sa takie same
					{
						error = true;
						//cout << "Los pytania sie powtarza" << endl;
					}
				}
				for (i = 0; i < NUMBER_OF_QUESTIONS; i++)
				{
					if (UsedArray[i] == temp && UsedIndex != (NUMBER_OF_QUESTIONS - 1)) //Sprawdz czy juz byly takie pary
					{
						error = true;
						//cout << "Question already used" << endl;
					}
					else if (UsedIndex == (NUMBER_OF_QUESTIONS - 1))
					{
						error = false;
						UsedRestart();
						LoadUsed();
						UsedIndex = 0;
						cout << "Game Restarts" << endl;
					}
				}
			} while (error == true);

			good = temp;
			//cout << "OK! wylosowano: " << good << " dla pary" << endl;


			Pair[N] = good;
			cout << "Wprowadzono numer = " << Pair[N] << " dla pary: " << N + 1 << endl;
			cout << "UsedIndex = " << UsedIndex << endl;
			UsedArray[UsedIndex] = good;
			UsedIndex++;
			N++;

		} while (N != 2);

		cout << endl;

	}

	string TextMusic::TextWrapping(string str, int length)
	{
		int n = str.rfind(' ', length);
		if (n != std::string::npos) {
			str.at(n) = '\n';
		}

		return str;
	}

	void TextMusic::SaveUsed()
	{

		ofstream myfile(USED_MUSIC_TXT_FILEPATH);
		if (myfile.is_open())
		{
			for (int i = 0; i < NUMBER_OF_QUESTIONS; i++) {
				myfile << UsedArray[i] << endl;
			}
			myfile.close();
			//cout << "Used Saved properly" << endl;
		}
		else cout << "Unable to open file" << endl;

		ofstream myfile1(USED_INDEX_MUSIC_TXT_FILEPATH);
		if (myfile1.is_open())
		{
			myfile1 << UsedIndex;

			myfile1.close();
			//cout << "Used Saved properly" << endl;
		}
		else cout << "Unable to open file" << endl;

	}

	void TextMusic::LoadUsed()
	{

		ifstream File;
		File.open(USED_MUSIC_TXT_FILEPATH);

		int n = 0;

		while (!File.eof())
		{
			File >> UsedArray[n];
			n++;
		}

		File.close();

		for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
		{
			cout << "UsedArray[" << i + 1 << "] = " << UsedArray[i] << endl;
		}

		ifstream File1;
		File1.open(USED_INDEX_MUSIC_TXT_FILEPATH);

		n = 0;

		while (!File1.eof())
		{
			File1 >> UsedIndex;
			n++;
		}

	}

	void TextMusic::UsedRestart()
	{
		ofstream myfile(USED_MUSIC_TXT_FILEPATH);
		if (myfile.is_open())
		{
			for (int i = 0; i < NUMBER_OF_QUESTIONS; i++) {
				myfile << "0" << endl;
			}
			myfile.close();
			cout << "Used Restarted Properly" << endl;
		}
		else cout << "Unable to open file";
	}

	void TextMusic::SaveBlockNums()
	{
		ofstream myfile(BLOCK_NUMS_TXT_FILEPATH);
		if (myfile.is_open())
		{
			for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
				myfile << nums[i] << endl;
			}
			myfile.close();
			//cout << "Block Nums Saved" << endl;
		}
		else cout << "Unable to open file" << endl;
	}

	void TextMusic::ClearBlockNums()
	{
		ofstream myfile(BLOCK_NUMS_TXT_FILEPATH);
		if (myfile.is_open())
		{
			for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
				myfile << "0" << endl;
			}
			myfile.close();
			cout << "Block Nums Cleared" << endl;
		}
		else cout << "Unable to open file";
	}

	void TextMusic::SavePairNums()
	{
		ofstream myfile1(PAIR1_TXT_FILEPATH);
		if (myfile1.is_open())
		{
			for (int i = 0; i < 2; i++) {
				myfile1 << nums[i] << endl;
			}
			myfile1.close();
			//cout << "Question Nums Saved" << endl;
		}
		else cout << "Unable to open file" << endl;

		ofstream myfile2(PAIR2_TXT_FILEPATH);
		if (myfile2.is_open())
		{
			for (int i = 2; i < 4; i++) {
				myfile2 << nums[i] << endl;
			}
			myfile2.close();
			//cout << "Question Nums Saved" << endl;
		}
		else cout << "Unable to open file" << endl;
	}

	void TextMusic::LoadPoints()
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
	}

	int TextMusic::ReturnUsedIndex()
	{
		return UsedIndex;
	}


	void TextMusic::DrawText()
	{
		for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
		{
			this->_data->window.draw(this->text[i]);
		}
		for (int i = 0; i < 2; i++)
		{
			this->_data->window.draw(this->PlayerData[i]);
		}
	}
	void TextMusic::DrawCorrect(bool correct)
	{
		if (correct == true)
		{
			this->_data->window.draw(this->Correct[0]);
		}
		else if (correct == false)
		{
			this->_data->window.draw(this->Correct[1]);
		}
	}
	void TextMusic::DrawHowTo()
	{
		this->_data->window.draw(this->PressF1);
	}
	void TextMusic::DrawEND()
	{
		this->_data->window.draw(this->END);
	}
}