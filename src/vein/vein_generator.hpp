#pragma once

#include "glm_to_tps.hpp"
#include "vein_mesh.hpp"

namespace vein
{
	class VeinGenerator
	{
	public:
		static VeinGenerator& getInstance();

		VeinMesh createBifurcation(float angleLeft, float angleRight) const;
		VeinMesh createCylinder() const;

	private:
		VeinGenerator() {}
		TempMesh createFlatBifurcationSegment() const;
		TempMesh createRotatedMesh(const TempMesh& mesh, float angle) const;
		void removeDuplicatedVertices(TempMesh& mesh) const;
		void fillControlPoints(float angleLeft, float angleRight, std::vector<Domain_Point>& domainPoints, std::vector<Range_Point>& rangePoints) const;
		TempMesh createCombinedBaseBifurcation();
		TempMesh createBaseRangePoints();

		TempMesh bifurcationBase = createCombinedBaseBifurcation();
		TempMesh baseRangePoints = createBaseRangePoints();
		TempMesh leftBranchRangePoints = createRotatedMesh(baseRangePoints, glm::pi<float>() * 2.0f / 3.0f);
		TempMesh rightBranchRangePoints = createRotatedMesh(baseRangePoints, glm::pi<float>() * 4.0f / 3.0f);
	};
}