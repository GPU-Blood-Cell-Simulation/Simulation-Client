#pragma once

#include "../defines.hpp"
#include "glm_to_tps.hpp"
#include "vein_mesh.hpp"

namespace vein
{
	namespace VeinGenerator
	{
		VeinMesh createBifurcation(float radiusTop, float radiusLeft, float radiusRight,
			float rollLeft, float rollRight, float pitchLeft, float pitchRight);
		VeinMesh createCylinder(float radiusTop, float radius, int vLayers, float skewRoll, float skewPitch);
	}
}