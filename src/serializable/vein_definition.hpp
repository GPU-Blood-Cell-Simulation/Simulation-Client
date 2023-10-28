#pragma once

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct VeinDefinition
	{

	};

	inline void to_json(json& j, const VeinDefinition& o)
	{
		j = json{};
	}

	inline void from_json(const json& j, VeinDefinition& o)
	{

	}
}