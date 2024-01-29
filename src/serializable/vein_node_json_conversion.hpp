#pragma once

#include "../vein/nodes/root_node.hpp"
#include "../vein/nodes/cylinder_node.hpp"
#include "../vein/nodes/bifurcation_node.hpp"

#include <nlohmann/json.hpp>

namespace vein
{
	using json = nlohmann::json;

	inline void to_json(json& j, const auto& o)
	{
		j = o.generateJson();
	}

}