#pragma once

#include "../vein/nodes/root_node.hpp"

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct VeinDefinition
	{
		std::unique_ptr<vein::Node> rootNode = std::make_unique<vein::RootNode>();
	};

	inline void to_json(json& j, const VeinDefinition& o)
	{
		j = json{};
	}

	inline void from_json(const json& j, VeinDefinition& o)
	{

	}
}