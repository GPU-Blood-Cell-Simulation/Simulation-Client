#pragma once

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct Spring
	{
		int start = -1;
		int end = -1;
		int length = 1;
	};

	inline void to_json(json& j, const Spring& o)
	{
		j = json{ {"start", o.start}, {"end", o.end}, {"length", o.length} };
	}

	inline void from_json(const json& j, Spring& o)
	{
		j.at("start").get_to(o.start);
		j.at("end").get_to(o.end);
		j.at("length").get_to(o.length);
	}
}