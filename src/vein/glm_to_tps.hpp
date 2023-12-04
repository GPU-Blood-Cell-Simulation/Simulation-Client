#pragma once

#include <glm/vec3.hpp>
#include <tps/tps.hpp>

namespace vein
{
	using Transformation =  tps::Thin_plate_spline_transformation<3, 3>;
	using Domain_Point = Transformation::Domain_point;
	using Range_Point = Transformation::Range_point;

	// Conversions between glm and tps data structures

	template<typename T>
	inline glm::vec3 toGLM(T p)
	{
		return glm::vec3(p(0), p(1), p(2));
	}

	inline Domain_Point toDP(const glm::vec3& v)
	{
		return Domain_Point(v.x, v.y, v.z);
	}

	inline Range_Point toRP(const glm::vec3& v)
	{
		return Range_Point(v.x, v.y, v.z);
	}
}