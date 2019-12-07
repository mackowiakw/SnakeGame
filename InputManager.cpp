#pragma once
#include <string>
#include "InputManager.hpp"
#include "DEFINITIONS.hpp"


namespace wm
{
	bool InputManager::IsEnterKey(sf::Uint32 const keyCode)
	{
		return keyCode == 13;
	}

	bool InputManager::IsBackspaceKey(sf::Uint32 const keyCode)
	{
		return keyCode == 8;
	}

	bool InputManager::IsAlphaCharacter(sf::Uint32 const keyCode)
	{
		return keyCode >= 65 && keyCode <= 122;
	}

}
