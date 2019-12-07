#pragma once
#include "MathHelper.hpp"
#include <random>
//#include <algorithm>

namespace wm
{

	//	Due to compiling error with unresolved externals (when linking)
	//	Class declared and defined as inline in .hpp file

	/*template<typename T>
	T MathHelper<T>::random(T min, T max)
	{
		std::default_random_engine engine{ std::random_device{}() };

		using dist = std::conditional_t<
			std::is_integral<T>::value,
			std::uniform_int_distribution<T>,
			std::uniform_real_distribution<T>
		>;

		return dist{ min, max }(engine);
	}
	
	//returns true if (lower < value < greater)
	//
	template<typename T>
	bool MathHelper<T>::between(const T value, const T lower, const T greater)
	{
		if (value == lower)
		{
			return false;
		}
		else
		{
			return static_cast<unsigned>(value - lower) < greater - lower;
		}
	}*/

}