#pragma once

#include "glm_to_tps.hpp"
#include "vein_mesh.hpp"

namespace vein
{
	class VeinGenerator
	{
	public:
		VeinMesh createBifurcation(float angleLeft, float angleRight);
		VeinMesh createCylinder();

	private:
		TempMesh createFlatBifurcationSegment();
		TempMesh createRotatedMesh(const TempMesh& mesh, float angle);
		void removeDuplicatedVertices(TempMesh& mesh);
		void fillControlPoints(const TempMesh& mesh, float angleLeft, float angleRight, std::vector<Domain_Point>& domainPoints, std::vector<Range_Point>& rangePoints);
		TempMesh createCombinedFlatBifurcation();
		TempMesh createBaseRangePoints();

		TempMesh bifurcationBase = createCombinedFlatBifurcation();
		TempMesh baseRangePoints = createBaseRangePoints();
		TempMesh leftBranchRangePoints = createRotatedMesh(baseRangePoints, glm::pi<float>() * 2.0f / 3.0f);
		TempMesh rightBranchRangePoints = createRotatedMesh(baseRangePoints, glm::pi<float>() * 4.0f / 3.0f);;
	};
}