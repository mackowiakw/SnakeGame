#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace wm
{
	constexpr auto SNAKE_ELEMENT_SIZE{ 25 };
	const auto SNAKE_COLOR = sf::Color::White;
	const auto SNACK_COLOR = sf::Color::Red;

	const auto TEXT_COLOR = sf::Color::Cyan;
	constexpr auto SCORE_TABLE_MAX_SIZE{ 5 };
	constexpr auto PLAYER_NICK_MAX_LENGTH{ 10 };

	constexpr auto FRAMERATE{ 15 };
	constexpr auto FONT_SIZE{ 25 };

	constexpr auto SCREEN_WIDTH{ 800 };
	constexpr auto SCREEN_HEIGHT{ 450 };

	constexpr auto X_LENGHT{ static_cast<int>(SCREEN_WIDTH / SNAKE_ELEMENT_SIZE) };
	constexpr auto Y_LENGHT{ static_cast<int>(SCREEN_HEIGHT / SNAKE_ELEMENT_SIZE) };
	constexpr auto X_MIDDLE{ static_cast<int>(X_LENGHT / 2) };
	constexpr auto Y_MIDDLE{ static_cast<int>(Y_LENGHT / 2) };

	constexpr auto EMPTY_FIELD{ 0 };
	constexpr auto SNACK_FIELD{ 21371488 };

	const std::string FONT_FILEPATH{ "Resources/OpenSans-Regular.ttf" };
	const std::string SCORES_FILEPATH{ "Resources/high_score.txt" };

	enum DIRECTIONS
	{
		RIGHT, DOWN, LEFT, UP
	};

}
