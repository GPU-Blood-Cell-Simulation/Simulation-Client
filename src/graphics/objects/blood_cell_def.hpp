#pragma once

#include "spring.hpp"

#include <vector>

namespace graphics
{
	class BloodCellDef
	{
		int count = 0;
		int particlesInCell = 0;
		std::vector<Spring> springs;
	};
}