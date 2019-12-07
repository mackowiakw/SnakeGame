#pragma once
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Snack.hpp"
#include "Snake.hpp"
#include "Game.hpp"

namespace wm
{
	class GameManager : protected Game
	{
	private:

		static std::array< std::array<int, Y_LENGHT>, X_LENGHT > gameArray_;
		static std::vector<std::pair<std::string, int>> scoreTable_;
		static std::string playerNick_;
		static int playerScore_;
		static sf::Text scoreTableTxt_;

	public:

		static void setScore(const int score);
		static bool isSnakeHere(CordsType const& cords);
		static bool isThisPointFree(CordsType const& cords);
		static void showGameArray();
		static void gameOver(sf::RenderWindow& window);
		static void waitForStart(sf::RenderWindow& window);
		static void displayScores(sf::RenderWindow& window);
		static void start(sf::RenderWindow& window, std::shared_ptr<Snake> snake, std::shared_ptr<Snack> snack);

		static std::array<std::array<int, Y_LENGHT>, X_LENGHT>& getGameArrayRef();
	};


}
