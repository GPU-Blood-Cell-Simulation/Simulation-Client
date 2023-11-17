#include "vein_generator.hpp"

#include "../defines.hpp"

namespace vein
{
	TempMesh VeinGenerator::createFlatBifurcationSegment()
	{
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices;

		static constexpr float triangleH = base::veinHeight / base::vLayers;
		static constexpr float radianBatch = 2 * glm::pi<float>() / base::hLayers;
		static constexpr float triangleBase = radianBatch * base::veinRadius;
		for (int i = 0; i < base::vLayers; ++i)
		{
			float h = i * triangleH;
			for (int j = 0; j < base::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// flat 1/3 of a bifurcation
				glm::vec3 position = glm::vec3(
					base::veinRadius * cos(angle),
					h,
					0
				);

				static constexpr float alpha = 2.0f / 3.0f;
				float transformRadius = glm::sqrt(position.x * position.x + position.y * position.y);
				float transformAngle = glm::atan(position.x, position.y);

				position.x = glm::pow(transformRadius, alpha) * glm::sin(alpha * transformAngle);
				position.y = glm::pow(transformRadius, alpha) * glm::cos(alpha * transformAngle);
				position.z = cylinder::veinRadius * sin(angle);

				positions.push_back(position);

				if (i < base::vLayers / 2 - 1)
				{
					int nextj = (j + 1) % base::hLayers;
					indices.push_back((i + 1) * base::hLayers + j);
					indices.push_back(i * base::hLayers + j);
					indices.push_back(i * base::hLayers + nextj);
					indices.push_back((i + 1) * base::hLayers + j);
					indices.push_back(i * base::hLayers + nextj);
					indices.push_back((i + 1) * base::hLayers + nextj);
				}
			}
		}

		return TempMesh(std::move(positions), std::move(indices));
	}


	TempMesh VeinGenerator::createRotatedMesh(const TempMesh& mesh, float angle)
	{
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices = mesh.indices;

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));

		for (auto&& position : mesh.positions)
		{
			positions.emplace_back(rotation * glm::vec4(position, 1.0f));
		}

		return TempMesh(std::move(positions), std::move(indices));
	}


	TempMesh VeinGenerator::createCombinedFlatBifurcation()
	{
		TempMesh base = createFlatBifurcationSegment();
		TempMesh left = createRotatedMesh(base, glm::pi<float>() * 2 / 3);
		TempMesh right = createRotatedMesh(base, glm::pi<float>() * -2 / 3);

		int indicesSize = base.indices.size();
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices(indicesSize * 3);

		positions.insert(positions.end(), base.positions.begin(), base.positions.end());
		positions.insert(positions.end(), left.positions.begin(), left.positions.end());
		positions.insert(positions.end(), right.positions.begin(), right.positions.end());

		indices.insert(indices.begin(), base.indices.begin(), base.indices.end());

		for (int i = 0; i < indicesSize; i++)
		{
			indices.push_back(left.indices[i] + base::segmentVertexCount);
		}

		for (int i = 0; i < indicesSize; i++)
		{
			indices.push_back(right.indices[i] + 2 * base::segmentVertexCount);
		}

		// TODO: remove repeating vertices 

		return TempMesh(std::move(positions), std::move(indices));
	}

	void VeinGenerator::removeDuplicatedVertices(TempMesh& mesh)
	{
		//// Remove half of the first row from the left branch - the one that collides with base
		//mesh.positions.erase(mesh.positions.begin() + base::segmentVertexCount, mesh.positions.begin() + base::segmentVertexCount + base::hLayers);

		//int leftBranchIndicesStart = (base::segmentVertexCount - base::hLayers) * 6;
		//mesh.indices.erase(mesh.indices.begin() + leftBranchIndicesStart, mesh.indices.begin() + leftBranchIndicesStart + base::hLayers * 6);

		//// Adjust all the following indices
		//std::for_each(mesh.indices.begin() + leftBranchIndicesStart, mesh.indices.end(), [&](auto& index)
		//	{
		//		index -= base::hLayers;
		//	});

		//// Remove the whole first row from the right branch
		//mesh.positions.erase(mesh.positions.begin() + 2 * base::segmentVertexCount - base::hLayers, mesh.positions.begin() + 2 * base::segmentVertexCount);

		//int rightBranchIndicesStart = (base::segmentVertexCount - base::hLayers) * 6;
		//mesh.indices.erase(mesh.indices.begin() + rightBranchIndicesStart, mesh.indices.begin() + rightBranchIndicesStart + base::hLayers * 6);

		//// Adjust all the following indices
		//std::for_each(mesh.indices.begin() + rightBranchIndicesStart, mesh.indices.end(), [&](auto& index)
		//	{
		//		index -= base::hLayers;
		//	});

	}

	void VeinGenerator::fillControlPoints(const TempMesh& mesh, float angleLeft, float angleRight, std::vector<Domain_Point>& domainPoints, std::vector<Range_Point>& rangePoints)
	{
		// base - last ring of base mesh
		for (int i =0; i < base::hLayers; i += 5)
		{
			// TODO : larger/smaller radius
			domainPoints.emplace_back(toDP(mesh.positions[i + base::segmentVertexCount - base::hLayers]));

			rangePoints.emplace_back(toRP(baseRangePoints.positions[i]));
		}
		// left
		for (int i = 0; i < base::hLayers; i += 5)
		{
			domainPoints.emplace_back(toDP(mesh.positions[i + 2 * base::segmentVertexCount - base::hLayers]));

			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() - angleLeft, glm::vec3(0, 0, 1));

			rangePoints.emplace_back(toRP(rotation * glm::vec4(baseRangePoints.positions[i], 1.0f) + glm::vec4(0, 0, 0, 0)));
		}
		// right
		for (int i = 0; i < base::hLayers; i += 5)
		{
			domainPoints.emplace_back(toDP(mesh.positions[i + 3 * base::segmentVertexCount - base::hLayers]));

			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() + angleRight, glm::vec3(0, 0, 1));

			rangePoints.emplace_back(toRP(rotation * glm::vec4(baseRangePoints.positions[i], 1.0f) + glm::vec4(0, 0, 0, 0)));
		}
	}

	TempMesh VeinGenerator::createBaseRangePoints()
	{
		std::vector<glm::vec3> positions;
		static constexpr float triangleH = cylinder::veinHeight / cylinder::vLayers;
		static constexpr float radianBatch = 2 * glm::pi<float>() / cylinder::hLayers;
		static float triangleBase = radianBatch * cylinder::veinRadius;
		static constexpr float h = (cylinder::vLayers - 1) * triangleH;

		for (int i = 0; i < cylinder::hLayers; ++i)
		{
			float angle = i * radianBatch;

			// normal vein
			positions.emplace_back(
				cylinder::veinRadius * cos(angle),
				h,
				cylinder::veinRadius * sin(angle)
			);
		}

		return TempMesh(std::move(positions), std::vector<unsigned int>());
	}


	VeinMesh VeinGenerator::createBifurcation(float angleLeft, float angleRight)
	{
		TempMesh bifurcation = createCombinedFlatBifurcation();
		removeDuplicatedVertices(bifurcation);

		std::vector<Domain_Point> domainPoints;
		std::vector<Range_Point> rangePoints;

		fillControlPoints(bifurcation, angleLeft, angleRight, domainPoints, rangePoints);

		// Calculate the thin plate spline transformation from control points
		Transformation tps(domainPoints.begin(), domainPoints.end(), rangePoints.begin(), rangePoints.end());

		// Transform vertices
		std::vector<glm::vec3> transfromedPositions;
		for (auto&& position : bifurcation.positions)
		{
			transfromedPositions.emplace_back(toGLM(tps.transform(toDP(position))));
		}

		return VeinMesh(std::move(transfromedPositions), std::move(bifurcation.indices));
	}


	VeinMesh VeinGenerator::createCylinder()
	{
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices;

		float triangleH = cylinder::veinHeight / cylinder::vLayers;
		constexpr float radianBatch = 2 * glm::pi<float>() / cylinder::hLayers;
		float triangleBase = radianBatch * cylinder::veinRadius;
		for (int i = 0; i < cylinder::vLayers; ++i)
		{
			float h = i * triangleH /*- height / 2*/;
			for (int j = 0; j < cylinder::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// normal vein
				positions.emplace_back(
					cylinder::veinRadius * cos(angle),
					h,
					cylinder::veinRadius * sin(angle)
				);

				if (i < cylinder::vLayers - 1)
				{
					int nextj = (j + 1) % cylinder::hLayers;
					indices.emplace_back((i + 1) * cylinder::hLayers + j);
					indices.emplace_back(i * cylinder::hLayers + j);
					indices.emplace_back(i * cylinder::hLayers + nextj);
					indices.emplace_back((i + 1) * cylinder::hLayers + j);
					indices.emplace_back(i * cylinder::hLayers + nextj);
					indices.emplace_back((i + 1) * cylinder::hLayers + nextj);
				}
			}
		}

		return VeinMesh(std::move(positions), std::move(indices));
	}
}