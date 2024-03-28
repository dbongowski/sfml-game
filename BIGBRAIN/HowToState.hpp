#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <string>
#include <iostream>

namespace Bongo
{
	class HowToState : public State
	{
	
	public:
		HowToState(GameDataRef data);

		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:

		GameDataRef _data;
		sf::Clock _clock;

		sf::Text exit;
		sf::Sprite animation;
	};
}
