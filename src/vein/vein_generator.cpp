#include "vein_generator.hpp"

#include "../defines.hpp"

namespace vein
{
	VeinGenerator& VeinGenerator::getInstance()
	{
		static VeinGenerator instance;
		return instance;
	}


	TempMesh VeinGenerator::createFlatBifurcationSegment() const
	{
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices;

		static constexpr float triangleH = bif::veinHeight / bif::vLayers;
		static constexpr float radianBatch = 2 * glm::pi<float>() / bif::hLayers;
		static constexpr float triangleBase = radianBatch * bif::veinRadius;
		for (int i = 0; i < bif::vLayers; ++i)
		{
			float h = i * triangleH;
			for (int j = 0; j < bif::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// flat 1/3 of a bifurcation
				glm::vec3 position = glm::vec3(
					bif::veinRadius * cos(angle),
					h,
					0
				);

				static constexpr float alpha = 2.0f / 3.0f;
				float transformRadius = glm::sqrt(position.x * position.x + position.y * position.y);
				float transformAngle = glm::atan(position.x, position.y);

				position.x = glm::pow(transformRadius, alpha) * glm::sin(alpha * transformAngle);
				position.y = glm::pow(transformRadius, alpha) * glm::cos(alpha * transformAngle);
				position.z = cyl::veinRadius * sin(angle);

				positions.push_back(position);

				if (i < bif::vLayers - 1)
				{
					int nextj = (j + 1) % bif::hLayers;
					indices.push_back((i + 1) * bif::hLayers + j);
					indices.push_back(i * bif::hLayers + j);
					indices.push_back(i * bif::hLayers + nextj);
					indices.push_back((i + 1) * bif::hLayers + j);
					indices.push_back(i * bif::hLayers + nextj);
					indices.push_back((i + 1) * bif::hLayers + nextj);
				}
			}
		}

		return TempMesh(std::move(positions), std::move(indices));
	}


	TempMesh VeinGenerator::createRotatedMesh(const TempMesh& mesh, float angle) const
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


	TempMesh VeinGenerator::createCombinedBaseBifurcation()
	{
		TempMesh base = createFlatBifurcationSegment();
		TempMesh left = createRotatedMesh(base, glm::pi<float>() * 2 / 3);
		TempMesh right = createRotatedMesh(base, glm::pi<float>() * -2 / 3);

		int indicesSize = base.indices.size();
		std::vector<glm::vec3> positions;
		positions.reserve(3 * base.positions.size());
		std::vector<unsigned int> indices;
		indices.reserve(indicesSize * 3);

		positions.insert(positions.end(), base.positions.begin(), base.positions.end());
		positions.insert(positions.end(), left.positions.begin(), left.positions.end());
		positions.insert(positions.end(), right.positions.begin(), right.positions.end());

		indices.insert(indices.begin(), base.indices.begin(), base.indices.end());

		for (int i = 0; i < indicesSize; i++)
		{
			indices.push_back(left.indices[i] + bif::vLayers  * bif::hLayers);
		}

		for (int i = 0; i < indicesSize; i++)
		{
			indices.push_back(right.indices[i] + 2 * bif::vLayers * bif::hLayers);
		}

		// remove repeating vertices 
		TempMesh bifuraction(std::move(positions), std::move(indices));

		return bifuraction;
	}

	void VeinGenerator::fillControlPoints(float angleLeft, float angleRight,
		std::vector<Domain_Point>& domainPoints, std::vector<Range_Point>& rangePoints) const
	{
		// base - last ring of base mesh
		for (int i =0; i < 2 * bif::hLayers; i += 2)
		{
			// TODO : larger/smaller radius
			domainPoints.emplace_back(toDP(bifurcationBase.positions[i + bif::segmentVertexCount - 2 *bif::hLayers]));

			rangePoints.emplace_back(toRP(baseRangePoints.positions[i]));
		}
		// left
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			domainPoints.emplace_back(toDP(bifurcationBase.positions[i + 2 * bif::segmentVertexCount - 2 * bif::hLayers]));

			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() + angleLeft, glm::vec3(0, 0, 1));

			rangePoints.emplace_back(toRP(rotation * glm::vec4(baseRangePoints.positions[i], 1.0f) + glm::vec4(0, 0, 0, 0)));
		}
		// right
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			domainPoints.emplace_back(toDP(bifurcationBase.positions[i + 3 * bif::segmentVertexCount - 2 * bif::hLayers]));

			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() + angleRight, glm::vec3(0, 0, 1));

			rangePoints.emplace_back(toRP(rotation * glm::vec4(baseRangePoints.positions[i], 1.0f) + glm::vec4(0, 0, 0, 0)));
		}
	}

	TempMesh VeinGenerator::createBaseRangePoints()
	{
		std::vector<glm::vec3> positions;
		static constexpr float triangleH = bif::veinHeight / bif::vLayers;
		static constexpr float radianBatch = 2 * glm::pi<float>() / bif::hLayers;
		static constexpr float hPrev = (bif::vLayers - 2) * triangleH;
		static constexpr float hLast = (bif::vLayers - 1) * triangleH;

		auto fill = [&](float h)
			{
				for (int i = 0; i < bif::hLayers; ++i)
				{
					float angle = i * radianBatch;

					// normal vein
					positions.emplace_back(
						bif::veinRadius * cos(angle),
						h,
						bif::veinRadius * sin(angle)
					);
				}
			};
		fill(hPrev);
		fill(hLast);

		return TempMesh(std::move(positions), std::vector<unsigned int>());
	}


	VeinMesh VeinGenerator::createBifurcation(float angleLeft, float angleRight) const
	{
		std::vector<Domain_Point> domainPoints;
		std::vector<Range_Point> rangePoints;

		fillControlPoints(angleLeft, angleRight, domainPoints, rangePoints);

		// Calculate the thin plate spline transformation from control points
		Transformation tps(domainPoints.begin(), domainPoints.end(), rangePoints.begin(), rangePoints.end());

		// Transform vertices
		std::vector<glm::vec3> transfromedPositions(bifurcationBase.positions.size());

		#pragma omp parallel for
		for (int i = 0; i < bifurcationBase.positions.size(); i++)
		{
			transfromedPositions[i] = toGLM(tps.transform(toDP(bifurcationBase.positions[i])));
		}
		return VeinMesh(std::move(transfromedPositions), bifurcationBase.indices);
	}


	VeinMesh VeinGenerator::createCylinder(int vLayers) const
	{
		std::vector<glm::vec3> positions;
		positions.reserve(vLayers * cyl::hLayers);
		std::vector<unsigned int> indices;
		indices.reserve(6 * (vLayers - 1) * cyl::hLayers);

		constexpr float radianBatch = 2 * glm::pi<float>() / cyl::hLayers;
		float triangleBase = radianBatch * cyl::veinRadius;
		for (int i = 0; i < vLayers; ++i)
		{
			float h = -i * cyl::triangleHeight;
			for (int j = 0; j < cyl::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// normal vein
				positions.emplace_back(
					cyl::veinRadius * cos(angle),
					h,
					cyl::veinRadius * sin(angle)
				);

				if (i < vLayers - 1)
				{
					int nextj = (j + 1) % cyl::hLayers;
					indices.emplace_back((i + 1) * cyl::hLayers + j);
					indices.emplace_back(i * cyl::hLayers + j);
					indices.emplace_back(i * cyl::hLayers + nextj);
					indices.emplace_back((i + 1) * cyl::hLayers + j);
					indices.emplace_back(i * cyl::hLayers + nextj);
					indices.emplace_back((i + 1) * cyl::hLayers + nextj);
				}
			}
		}

		return VeinMesh(std::move(positions), std::move(indices));
	}
}