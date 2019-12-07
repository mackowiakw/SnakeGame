#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include"DEFINITIONS.hpp"
#include "GameObject.hpp"

namespace wm
{
	class Snack final : public GameObject
	{
	private:

		CordsType cords_;
		std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef_;

	public:

		void newPosition();
		CordsType getPosition() const override;
		void draw(sf::RenderWindow& window) override;

		explicit Snack(std::array<std::array<int, Y_LENGHT>, X_LENGHT>& gameArrayRef);
	};

}
