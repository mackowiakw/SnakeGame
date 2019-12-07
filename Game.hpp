#pragma once
#include <SFML/Graphics.hpp>
#include "MathHelper.hpp"
#include <string>

namespace wm
{
	class Game
	{
	protected:
		
		using CordsType = sf::Vector2i;

		static sf::Font& getFontRef();
		static MathHelper<int> mathHelper;
		static void startRound();

	private:

		static struct MyException : public std::exception
		{
			const char* what() const noexcept;
		};

		static sf::Font font;
		static sf::RenderWindow window;
		static void readFontFromFile(std::string const& filepath) noexcept(false);
	

	public:
		
		Game();
		static void run();		
	};

}