#pragma once

#include <glm/vec3.hpp>
#include <tps/tps.hpp>

namespace vein
{
	using Transformation =  tps::Thin_plate_spline_transformation<3, 3>;
	using Domain_Point = Transformation::Domain_point;
	using Range_Point = Transformation::Range_point;

	// Conversions between glm and tps data structures

	/// <summary>
	/// Transforms a tps point into a glm 3D vector
	/// </summary>
	/// <param name="p">Either a Domain_Point or a Range_point</param>
	/// <returns></returns>
	inline glm::vec3 toGLM(const auto& p)
	{
		return glm::vec3(p(0), p(1), p(2));
	}

	/// <summary>
	/// Transforms a glm 3D vector into a tps domain point (starting coordinates)
	/// </summary>
	/// <param name="v">A glm 3D vector</param>
	/// <returns></returns>
	inline Domain_Point toDP(const glm::vec3& v)
	{
		return Domain_Point(v.x, v.y, v.z);
	}


	/// <summary>
	/// Transforms a glm 3D vector into a tps range point (result coordinates)
	/// </summary>
	/// <param name="v">A glm 3D vector</param>
	/// <returns></returns>
	inline Range_Point toRP(const glm::vec3& v)
	{
		return Range_Point(v.x, v.y, v.z);
	}
}