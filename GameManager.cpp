#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"
#include "InputManager.hpp"
#include "MathHelper.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <memory>
#include <utility>
#include <fstream>
#include <sstream>


namespace wm
{
	int GameManager::playerScore_{ 0 };
	std::string GameManager::playerNick_{};
	std::vector<std::pair<std::string, int>> GameManager::scoreTable_{};
	sf::Text GameManager::scoreTableTxt_{};
	std::array<std::array<int, Y_LENGHT>, X_LENGHT> GameManager::gameArray_{};

	bool GameManager::isSnakeHere(CordsType const& cords)
	{
		return MathHelper<int>::between(gameArray_.at(cords.x).at(cords.y), EMPTY_FIELD, SNACK_FIELD);
	}

	bool GameManager::isThisPointFree(CordsType const& cords)
	{
		return gameArray_.at(cords.x).at(cords.y) == EMPTY_FIELD;
	}

	void GameManager::setScore(const int score)
	{
		playerScore_ = score;
	}

	void GameManager::showGameArray()
	{
		system("cls");

		for (int y{ 0 }; y < Y_LENGHT; ++y)
		{
			for (int x{ 0 }; x < X_LENGHT; ++x)
			{
				std::cout << std::setw(5) << gameArray_.at(x).at(y);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::array<std::array<int, Y_LENGHT>, X_LENGHT>& GameManager::getGameArrayRef()
	{
		return gameArray_;
	}

	void GameManager::start(sf::RenderWindow& window, std::shared_ptr<Snake> snake, std::shared_ptr<Snack> snack)
	{
		window.clear();
		window.setFramerateLimit(FRAMERATE);

		playerScore_ = 2;
		playerNick_.erase();

		std::array<std::shared_ptr<GameObject>, 2> objectsPtrs = { snake, snack };

		while (window.isOpen())
		{
			sf::Event event{};
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					exit(0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					snake->setDirection(DIRECTIONS::LEFT);
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					snake->setDirection(DIRECTIONS::RIGHT);
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					snake->setDirection(DIRECTIONS::UP);
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					snake->setDirection(DIRECTIONS::DOWN);
					break;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
					return;
				}
			}

			if (isSnakeHere(snake->getNextHeadPosition()))
			{
				return;
			}
			else
			{
				if (snake->getNextHeadPosition() == snack->getPosition())
				{
					snake->eat();
					snack->newPosition();
				}
				else
				{
					snake->move();
				}
			}

			for (auto object : objectsPtrs)
			{
				object->draw(window);
			}

			window.display();
			window.clear();
		}
	}


	void GameManager::waitForStart(sf::RenderWindow& window)
	{
		window.clear();

		sf::Text text;
		text.setFont(Game::getFontRef());
		text.setString("PRESS SPACE TO START");
		text.setFillColor(TEXT_COLOR);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition((X_MIDDLE - 6) * SNAKE_ELEMENT_SIZE, (Y_MIDDLE)*SNAKE_ELEMENT_SIZE);

		window.draw(text);
		window.display();

		while (true)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					exit(0);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					return;
				}
			}
		}
	}

	void GameManager::gameOver(sf::RenderWindow& window)
	{
		window.clear();

		sf::Text text;
		text.setFont(Game::getFontRef());
		text.setFillColor(TEXT_COLOR);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition((X_MIDDLE - 8) * SNAKE_ELEMENT_SIZE, (Y_MIDDLE - 2) * SNAKE_ELEMENT_SIZE);


		sf::Event event{};
		while (window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				exit(0);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					exit(0);
				}
				break;
			case sf::Event::TextEntered:
				if (InputManager::IsEnterKey(event.text.unicode) && !playerNick_.empty())
				{
					return;
				}
				else if (InputManager::IsBackspaceKey(event.text.unicode))
				{
					if (!playerNick_.empty())
					{
						playerNick_.pop_back();
					}
				}
				else if (InputManager::IsAlphaCharacter(event.text.unicode))
				{
					if (playerNick_.length() < PLAYER_NICK_MAX_LENGTH)
					{
						playerNick_ += static_cast<char>(event.text.unicode);

						if (playerNick_.at(0) == '`')
						{
							playerNick_ = "";
						}
					}
				}
				break;
			default:
				break;
			}

			text.setString("Your score is: " + std::to_string(playerScore_) + "\n\nEnter Name: " + playerNick_);
			window.clear();
			window.draw(text);
			window.display();
		}
	}


	void GameManager::displayScores(sf::RenderWindow& window)
	{
		scoreTable_.erase(begin(scoreTable_), end(scoreTable_));

		std::ifstream inputScoreFile{ SCORES_FILEPATH };
		if (inputScoreFile)
		{
			std::string nick, score, line;

			while (std::getline(inputScoreFile, line))
			{
				std::istringstream lineStream{ line };
				if (std::getline(lineStream, nick, ';') && std::getline(lineStream, score))
				{
					if (nick.length() > PLAYER_NICK_MAX_LENGTH)
					{
						nick = nick.substr(0, PLAYER_NICK_MAX_LENGTH);
					}

					score.erase(std::remove_if(begin(score), end(score), isspace), end(score));

					if (!nick.empty() && std::none_of(begin(nick), end(nick), isdigit) &&
						!score.empty() && std::all_of(begin(score), end(score), isdigit))
					{
						scoreTable_.emplace_back(std::make_pair(nick, std::stoi(score)));
					}
				}
			}
			inputScoreFile.close();



			scoreTable_.emplace_back(std::make_pair(playerNick_, playerScore_));
			std::sort(begin(scoreTable_), end(scoreTable_), [](auto const& lhs, auto const& rhs) { return lhs.second > rhs.second; });
			if (scoreTable_.size() > SCORE_TABLE_MAX_SIZE)
			{
				scoreTable_.resize(SCORE_TABLE_MAX_SIZE);
			}

			std::ostringstream scores{};
			unsigned place{};

			scores << '\t' << std::left << std::setfill(' ') << std::setw(20) << "nick" << "score\n\n";
			for (auto const& playerData : scoreTable_)
			{
				scores << ++place << '\t' << std::left << std::setfill(' ') << std::setw(20) << playerData.first << playerData.second << "\n\n";
			}
			scoreTableTxt_.setString(scores.str());

		}


		std::ofstream outputScoreFile{ SCORES_FILEPATH, std::ios::trunc };
		if (outputScoreFile)
		{
			std::string nextLine{};
			for (auto const& playerData : scoreTable_)
			{
				outputScoreFile << nextLine << playerData.first << ';' << playerData.second;
				nextLine = '\n';
			}
			outputScoreFile.close();
		}

		scoreTableTxt_.setFont(Game::getFontRef());
		scoreTableTxt_.setFillColor(TEXT_COLOR);
		scoreTableTxt_.setCharacterSize(static_cast<int>(FONT_SIZE/1.5f));
		scoreTableTxt_.setPosition(3 * SNAKE_ELEMENT_SIZE, 1 * SNAKE_ELEMENT_SIZE);

		sf::Text text;
		text.setFont(Game::getFontRef());
		text.setString("PRESS ENTER");
		text.setFillColor(TEXT_COLOR);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition((X_MIDDLE - 3) * SNAKE_ELEMENT_SIZE, (Y_MIDDLE + 4) * SNAKE_ELEMENT_SIZE);


		window.clear();
		window.draw(text);
		window.draw(scoreTableTxt_);
		window.display();


		while (true)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
					return;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					return;
				}
			}
		}

	}




}
