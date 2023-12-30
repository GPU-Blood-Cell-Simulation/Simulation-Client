#pragma once

#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

// Hijacking a library namespace is a bad practice but nlohmann gives us no noiche
namespace glm
{
    using json = nlohmann::json;

    inline void to_json(json& j, const vec3& o)
	{
		j = json{ {"x", o.x}, {"y", o.y}, {"z", o.z} };
	}

	inline void from_json(const json& j, vec3& o)
	{
		j.at("x").get_to(o.x);
		j.at("y").get_to(o.y);
        j.at("z").get_to(o.z);
	}
}