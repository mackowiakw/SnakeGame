#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

namespace wm
{
	class Snake final : public GameObject
	{
	private:

		int size_, direction_;
		CordsType head_, velocity_{ -1, -1 };
		std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef_;

	public:

		void eat();
		void move();
		void setNewHead();
		int getScore() const;

		void setDirection(int newDirection);
		CordsType getNextHeadPosition() const;

		CordsType getPosition() const override;
		void draw(sf::RenderWindow& window) override;
	
		explicit Snake(std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef);
	};

}
