#pragma once
#include <SFML\Graphics.hpp>
#include "Game.hpp"

namespace wm
{
	// pure virtual generic GameObject class
	// contains virtual function:
	// --void draw(sf::RenderWindow&) = 0
	// --sf::Vector2i getPosition() const = 0
	//
	class GameObject : protected Game
	{
	public:

		virtual void draw(sf::RenderWindow& window) = 0;
		virtual CordsType getPosition() const = 0;
	};

}