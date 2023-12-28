#pragma once

#include "../defines.hpp"
#include "glm_to_tps.hpp"
#include "vein_mesh.hpp"

namespace vein
{
	class VeinGenerator
	{
	public:
		static VeinGenerator& getInstance();

		VeinMesh createBifurcation(float radiusTop, float radiusLeft, float radiusRight, float angleLeft, float angleRight) const;
		VeinMesh createCylinder(float radiusTop, float radius, int vLayers, float skew) const;

	private:
		VeinGenerator() {}
		TempMesh createFlatBifurcationSegment(float radius) const;
		TempMesh createRotatedMesh(const TempMesh& mesh, float angle) const;
		void fillBifurcationControlPoints(std::array<Domain_Point, 3 * bif::hLayers>& domainPoints, std::array<Range_Point, 3 * bif::hLayers>& rangePoints,
			const TempMesh& scaledMesh, const TempMesh& scaledBaseRangePoints, float radiusTop, 
			float radiusLeft, float radiusRight, float angleLeft, float angleRight) const;
		TempMesh createCombinedBaseBifurcation(float radius) const;
		TempMesh createBaseRangePoints(float radius) const;
		void fillCylinderControlPoints(std::array<Domain_Point, 2 * bif::hLayers>& domainPoints, std::array<Range_Point, 2 * bif::hLayers>& rangePoints,
			const TempMesh& baseMesh, float radiusTop, float radius, int vLayers, float skew) const;
		TempMesh createBaseCylinder(float radiusTop, int vLayers) const;
	};
}