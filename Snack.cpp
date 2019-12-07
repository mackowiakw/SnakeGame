#pragma once
#include "Snack.hpp"
#include "DEFINITIONS.hpp"
#include "MathHelper.hpp"
#include "GameManager.hpp"
#include "Game.hpp"
#include "GameObject.hpp"

namespace wm
{

	using CordsType = sf::Vector2i;

	CordsType Snack::getPosition() const
	{	
		return cords_;
	}

	void Snack::draw(sf::RenderWindow& window)
	{
		sf::RectangleShape shape;
		shape.setFillColor(SNACK_COLOR);
		shape.setSize(sf::Vector2f{ SNAKE_ELEMENT_SIZE, SNAKE_ELEMENT_SIZE });
		shape.setPosition(sf::Vector2f{ sf::Vector2i{cords_.x * SNAKE_ELEMENT_SIZE, cords_.y * SNAKE_ELEMENT_SIZE} });

		window.draw(shape);
	}

	void Snack::newPosition()
	{
		do
		{
			auto cordX = MathHelper<int>::random(0, X_LENGHT - 1);
			auto cordY = MathHelper<int>::random(0, Y_LENGHT - 1);

			cords_ = CordsType{ cordX, cordY };

		} while (!GameManager::isThisPointFree(cords_));

		gameArrayRef_.at(cords_.x).at(cords_.y) = SNACK_FIELD;
	}

	Snack::Snack(std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef)
		: gameArrayRef_{ gameArrayRef }
	{
		this->newPosition();
	}

}