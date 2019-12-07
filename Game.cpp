#include "Game.hpp"
#include "GameManager.hpp"
#include"Snack.hpp"
#include "Snake.hpp"
#include <memory>
#include <string>
#include <iostream>
#include <exception>

namespace wm
{

	sf::Font Game::font;
	sf::RenderWindow Game::window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT }, "Snake" };

	const char* Game::MyException::what() const noexcept
	{
		return "Couldn't read font from declared file!";
	}
 
	void Game::run()
	{
		window.setFramerateLimit(FRAMERATE);

		while (window.isOpen())
		{
			startRound();
		}
	}

	void Game::startRound()
	{
		GameManager gameManager{};
		std::shared_ptr<Snake> snakePtr = std::make_shared<Snake>( Snake{ gameManager.getGameArrayRef() } );
		std::shared_ptr<Snack> snackPtr = std::make_shared<Snack>( Snack{ gameManager.getGameArrayRef() } );
	
		gameManager.waitForStart(window);
		gameManager.start(window, snakePtr, snackPtr);
		gameManager.setScore(snakePtr->getScore());
		gameManager.gameOver(window);
		gameManager.displayScores(window);
	}

	sf::Font& Game::getFontRef()
	{
		return font;
	}

	void Game::readFontFromFile(std::string const& filepath)
	{
		if (!font.loadFromFile(filepath))
		{
			throw MyException();
		}
	}

	Game::Game()
	{
		try
		{
			readFontFromFile(FONT_FILEPATH);
		}
		catch (MyException execption)
		{
			std::cout << execption.what() << std::endl;
			window.close();
			exit(-1);
		}
	}

}
