#pragma once
#include "DEFINITIONS.hpp"
#include "Snake.hpp"
#include "GameManager.hpp"

namespace wm
{

	using CordsType = sf::Vector2i;

	CordsType Snake::getNextHeadPosition() const
	{
		CordsType _newHead{ head_ + velocity_ };
		_newHead += CordsType{ X_LENGHT, Y_LENGHT };
		_newHead.x %= X_LENGHT;
		_newHead.y %= Y_LENGHT;

		return _newHead;
	}

	void Snake::setNewHead()
	{
		head_ = getNextHeadPosition();
	}

	void Snake::eat()
	{
		++size_;
		setNewHead();
		gameArrayRef_.at(head_.x).at(head_.y) = size_ + 1;
	}

	void Snake::move()
	{
		setNewHead();
		gameArrayRef_.at(head_.x).at(head_.y) = size_ + 1;

		for (auto& row : gameArrayRef_) {
			std::for_each(begin(row), end(row), [](auto& value) { if (value && value != SNACK_FIELD) { value -= 1; } });
		}
	}

	CordsType Snake::getPosition() const
	{
		return head_;
	}

	int Snake::getScore() const
	{
		return size_;
	}

	void Snake::draw(sf::RenderWindow& window)
	{
		sf::RectangleShape shape;
		shape.setFillColor(SNAKE_COLOR);
		shape.setSize(sf::Vector2f{ SNAKE_ELEMENT_SIZE, SNAKE_ELEMENT_SIZE });

		for (int x{ 0 }; x < X_LENGHT; ++x) {
			for (int y{ 0 }; y < Y_LENGHT; ++y)
			{
				sf::Vector2i cords{ x, y };

				if (GameManager::isSnakeHere(cords))
				{
					shape.setPosition(sf::Vector2f{ sf::Vector2i{SNAKE_ELEMENT_SIZE * cords.x, SNAKE_ELEMENT_SIZE * cords.y} });
					window.draw(shape);
				}
			}
		}
	}

	void Snake::setDirection(const int newDirection) 
	{
		if ((direction_ + newDirection) % 2)
		{
			direction_ = newDirection;

			switch (newDirection)
			{
			case DIRECTIONS::RIGHT:
				velocity_ = { 1, 0 };
				break;

			case DIRECTIONS::DOWN:
				velocity_ = { 0, 1 };
				break;

			case DIRECTIONS::LEFT:
				velocity_ = { -1, 0 };
				break;

			case DIRECTIONS::UP:
				velocity_ = { 0, -1 };
				break;
			}
		}
	}

	Snake::Snake(std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef)
		: size_(2), head_(X_MIDDLE, Y_MIDDLE), direction_(DIRECTIONS::UP), gameArrayRef_(gameArrayRef)
	{
		this->setDirection(DIRECTIONS::LEFT);

		for (auto& row : gameArrayRef)
		{
			std::fill(begin(row), end(row), EMPTY_FIELD);
		}

		gameArrayRef.at(head_.x).at(head_.y) = size_;

		CordsType previousHead{ head_ - velocity_ };
		gameArrayRef.at(previousHead.x).at(previousHead.y) = size_ - 1;
	}
}
