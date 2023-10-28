#pragma once

#include "spring.hpp"

#include <vector>

namespace serializable
{
	using json = nlohmann::json;

	struct BloodCellType
	{
		int count = 0;
		int particlesInCell = 0;
		std::vector<Spring> springs;
	};

	inline void to_json(json& j, const BloodCellType& o)
	{
		j = json{ {"count", o.count}, {"particlesInCell", o.particlesInCell}, {"springs", o.springs} };
	}

	inline void from_json(const json& j, BloodCellType& o)
	{
		j.at("count").get_to(o.count);
		j.at("particlesInCell").get_to(o.particlesInCell);
		j.at("springs").get_to(o.springs);
	}
}