#pragma once
#include <SFML/Graphics.hpp>

namespace wm
{
	class InputManager
	{
	public:

		static bool IsEnterKey(sf::Uint32 const keyCode);
		static bool IsBackspaceKey(sf::Uint32 const keyCode);
		static bool IsAlphaCharacter(sf::Uint32 const keyCode);
	};

}
