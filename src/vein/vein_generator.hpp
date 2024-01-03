#pragma once

#include "../defines.hpp"
#include "glm_to_tps.hpp"
#include "vein_mesh.hpp"

namespace vein
{
	/// <summary>
	/// Functions that create a vein segment from the parameters specified
	/// </summary>
	namespace VeinGenerator
	{
		/// <summary>
		/// Creates a bifurcation segment
		/// </summary>
		/// <param name="radiusTop">Radius of the node's parent's ending that this segment will be attached to</param>
		/// <param name="radiusLeft">User-defined radius of the bifurcation's left branch</param>
		/// <param name="radiusRight">User-defined radius of the bifurcation's right branch</param>
		/// <param name="rollLeft">The roll angle of the bifurcation's left branch</param>
		/// <param name="rollRight">The roll angle of the bifurcation's right branch</param>
		/// <param name="pitchLeft">The pitch angle of the bifurcation's left branch</param>
		/// <param name="pitchRight">The pitch angle of the bifurcation's right branch</param>
		/// <returns></returns>
		VeinMesh createBifurcation(float radiusTop, float radiusLeft, float radiusRight,
			float rollLeft, float rollRight, float pitchLeft, float pitchRight);

		/// <summary>
		/// Creates a cylinder segment
		/// </summary>
		/// <param name="radiusTop">Radius of the node's parent's ending that this segment will be attached to</param>
		/// <param name="radius">User-defined radius of this segment's end</param>
		/// <param name="vLayers">The length of the segment described by an integer (number of vertical layers)</param>
		/// <param name="skewRoll">Skew of the vein with respect to the roll angle</param>
		/// <param name="skewPitch">Skew of the vein with respect to the pitch angle</param>
		/// <returns></returns>
		VeinMesh createCylinder(float radiusTop, float radius, int vLayers, float skewRoll, float skewPitch);
	}
}