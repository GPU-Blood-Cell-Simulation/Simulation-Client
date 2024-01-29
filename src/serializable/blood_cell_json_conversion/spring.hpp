#pragma once

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	/// <summary>
	/// Describes a single spring betweeen two particles in a blood cell
	/// </summary>
	struct Spring
	{
		int from = -1;
		int to = -1;

		bool operator==(const Spring&) const = default;
	};

	inline void to_json(json& j, const Spring& o)
	{
		j = json{ {"from", o.from}, {"to", o.to} };
	}

	inline void from_json(const json& j, Spring& o)
	{
		j.at("from").get_to(o.from);
		j.at("to").get_to(o.to);
	}
}