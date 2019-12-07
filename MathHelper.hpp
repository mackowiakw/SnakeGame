#pragma once
#include <random>

namespace wm
{
	template <typename T>
	class MathHelper
	{
	public:

		static T random(T min, T max)
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
		static bool between(const T value, const T lower, const T greater)
		{
			if (value == lower)
			{
				return false;
			}
			else
			{
				return static_cast<unsigned>(value - lower) < greater - lower;
			}
		}

	};


}
