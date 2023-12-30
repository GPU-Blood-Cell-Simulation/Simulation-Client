#include "vein_generator.hpp"

#include "../defines.hpp"


namespace vein
{
	static TempMesh createFlatBifurcationSegment(float radius)
	{
		std::vector<glm::vec3> positions;
		std::vector<unsigned int> indices;

		static constexpr float radianBatch = 2 * glm::pi<float>() / bif::hLayers;
		const float triangleH = bif::veinHeight / bif::vLayers * radius / bif::veinRadius;
		for (int i = 0; i < bif::vLayers; ++i)
		{
			float h = i * triangleH;
			for (int j = 0; j < bif::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// flat 1/3 of a bifurcation
				glm::vec3 position = glm::vec3(
					radius * cos(angle),
					h,
					0
				);

				static constexpr float alpha = 2.0f / 3.0f;
				float transformRadius = glm::sqrt(position.x * position.x + position.y * position.y);
				float transformAngle = glm::atan(position.x, position.y);

				position.x = glm::pow(transformRadius, alpha) * glm::sin(alpha * transformAngle);
				position.y = glm::pow(transformRadius, alpha) * glm::cos(alpha * transformAngle);
				position.z = radius * sin(angle);

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


	static TempMesh createRotatedMesh(const TempMesh& mesh, float angle)
	{
		std::vector<glm::vec3> positions(mesh.positions.size());
		std::vector<unsigned int> indices = mesh.indices;

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0, 1));

		#pragma omp parallel for
		for (int i = 0; i < mesh.positions.size(); i++)
		{
			positions[i] = rotation * glm::vec4(mesh.positions[i], 1.0f);
		}

		return TempMesh(std::move(positions), std::move(indices));
	}


	static TempMesh createCombinedBaseBifurcation(float radius)
	{
		TempMesh base = createFlatBifurcationSegment(radius);
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
			indices.emplace_back(left.indices[i] + bif::vLayers  * bif::hLayers);
		}

		for (int i = 0; i < indicesSize; i++)
		{
			indices.emplace_back(right.indices[i] + 2 * bif::vLayers * bif::hLayers);
		}

		return TempMesh(std::move(positions), std::move(indices));
	}

	static void fillBifurcationControlPoints(std::array<Domain_Point, 3 * bif::hLayers>& domainPoints, std::array<Range_Point, 3 * bif::hLayers>& rangePoints,
		const TempMesh& scaledMesh, const TempMesh& scaledBaseRangePoints, float radiusTop, float radiusLeft, float radiusRight, float yawLeft, float yawRight)
	{
		// base - last two rings of base mesh
		#pragma omp parallel for
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			domainPoints[i/2] = toDP(scaledMesh.positions[i + bif::segmentVertexCount - 2 * bif::hLayers]);
			rangePoints[i/2] = toRP(scaledBaseRangePoints.positions[i]);
		}

		// left
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() + yawLeft, glm::vec3(0, 0, 1));

		#pragma omp parallel for
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			domainPoints[i/2 + bif::hLayers] = toDP(scaledMesh.positions[i + 2 * bif::segmentVertexCount - 2 * bif::hLayers]);

			auto rangePos = scaledBaseRangePoints.positions[i];
			rangePos.x *= radiusLeft / radiusTop;
			rangePos.z *= radiusLeft / radiusTop;
			rangePoints[i/2 + bif::hLayers] = toRP(rotation * glm::vec4(rangePos, 1.0f));
		}

		// right
		rotation = glm::rotate(glm::mat4(1.0f), glm::pi<float>() + yawRight, glm::vec3(0, 0, 1));

		#pragma omp parallel for
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			domainPoints[i/2 + 2 * bif::hLayers] = (toDP(scaledMesh.positions[i + 3 * bif::segmentVertexCount - 2 * bif::hLayers]));

			auto rangePos = scaledBaseRangePoints.positions[i];
			rangePos.x *= radiusRight / radiusTop;
			rangePos.z *= radiusRight / radiusTop;
			rangePoints[i/2 + 2 * bif::hLayers] = toRP(rotation * glm::vec4(rangePos, 1.0f));
		}
	}

	static TempMesh createBaseRangePoints(float radius)
	{
		std::vector<glm::vec3> positions(2 * bif::hLayers);
		static constexpr float radianBatch = 2 * glm::pi<float>() / bif::hLayers;
		const float triangleH = bif::veinHeight / bif::vLayers * radius / bif::veinRadius;
		const float hPrev = (bif::vLayers - 2) * triangleH;
		const float hLast = (bif::vLayers - 1) * triangleH;

		#pragma omp parallel for
		for (int i = 0; i < bif::hLayers; ++i)
		{
			float angle = i * radianBatch;

			// normal vein
			positions[i] =
			{
				radius * cos(angle),
				hPrev,
				radius * sin(angle)
			};
		}
		#pragma omp parallel for
		for (int i = 0; i < bif::hLayers; ++i)
		{
			float angle = i * radianBatch;

			// normal vein
			positions[i + bif::hLayers] =
			{
				radius * cos(angle),
				hLast,
				radius * sin(angle)
			};
		}

		return TempMesh(std::move(positions), std::vector<unsigned int>());
	}


	VeinMesh VeinGenerator::createBifurcation(float radiusTop, float radiusLeft, float radiusRight, float yawLeft, float yawRight)
	{
		std::array<Domain_Point, 3 * bif::hLayers> domainPoints;
		std::array<Range_Point, 3 * bif::hLayers> rangePoints;

		TempMesh scaledMesh = createCombinedBaseBifurcation(radiusTop);
		TempMesh scaledBasePoints = createBaseRangePoints(radiusTop);

		fillBifurcationControlPoints(domainPoints, rangePoints, scaledMesh, scaledBasePoints, radiusTop, radiusLeft, radiusRight, yawLeft, yawRight);

		// Calculate the thin plate spline transformation from control points
		Transformation tps(domainPoints.begin(), domainPoints.end(), rangePoints.begin(), rangePoints.end());

		// Transform vertices
		std::vector<glm::vec3> transfromedPositions(scaledMesh.positions.size());

		#pragma omp parallel for
		for (int i = 0; i < scaledMesh.positions.size(); i++)
		{
			transfromedPositions[i] = toGLM(tps.transform(toDP(scaledMesh.positions[i])));
		}
		return VeinMesh(std::move(transfromedPositions), scaledMesh.indices);
	}


	static void fillCylinderControlPoints(std::array<Domain_Point, 2 * bif::hLayers>& domainPoints, std::array<Range_Point, 2 * bif::hLayers>& rangePoints,
			const TempMesh& baseMesh, float radiusTop, float radius, int vLayers, float skewYaw, float skewPitch)
	{
		// start - last two rings of base mesh
		#pragma omp parallel for
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			auto& rangePos = baseMesh.positions[i];
			domainPoints[i/2] = toDP(rangePos);
			rangePoints[i/2] = toRP(rangePos);
		}

		// end
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), skewPitch, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), skewYaw, glm::vec3(0, 0, 1));

		#pragma omp parallel for
		for (int i = 0; i < 2 * bif::hLayers; i += 2)
		{
			auto rangePos = baseMesh.positions[i + (vLayers - 2) * cyl::hLayers];
			domainPoints[i/2 + bif::hLayers] = toDP(rangePos);
			rangePos.x *= radius / radiusTop;
			rangePos.z *= radius / radiusTop;
			rangePoints[i/2 + bif::hLayers] = toRP(rotation * glm::vec4(rangePos, 1.0f));
		}
	}

	static TempMesh createBaseCylinder(float radiusTop, int vLayers)
	{
		std::vector<glm::vec3> positions;
		positions.reserve(vLayers * cyl::hLayers);
		std::vector<unsigned int> indices;
		indices.reserve(6 * (vLayers - 1) * cyl::hLayers);

		constexpr float radianBatch = 2 * glm::pi<float>() / cyl::hLayers;
		const float triangleBase = radianBatch * radiusTop;
		for (int i = 0; i < vLayers; ++i)
		{
			float h = -i * cyl::triangleHeight;
			for (int j = 0; j < cyl::hLayers; ++j)
			{
				float angle = j * radianBatch;

				// normal vein
				positions.emplace_back(
					radiusTop * cos(angle),
					h,
					radiusTop * sin(angle)
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

		return TempMesh(std::move(positions), std::move(indices));
	}

	VeinMesh VeinGenerator::createCylinder(float radiusTop, float radius, int vLayers, float skewYaw, float skewPitch)
	{
		std::array<Domain_Point, 2 * bif::hLayers> domainPoints;
		std::array<Range_Point, 2 * bif::hLayers> rangePoints;

		TempMesh baseMesh = createBaseCylinder(radiusTop, vLayers);

		fillCylinderControlPoints(domainPoints, rangePoints, baseMesh, radiusTop, radius, vLayers, skewYaw, skewPitch);

		// Calculate the thin plate spline transformation from control points
		Transformation tps(domainPoints.begin(), domainPoints.end(), rangePoints.begin(), rangePoints.end());

		// Transform vertices
		std::vector<glm::vec3> transfromedPositions(baseMesh.positions.size());

		#pragma omp parallel for
		for (int i = 0; i < baseMesh.positions.size(); i++)
		{
			transfromedPositions[i] = toGLM(tps.transform(toDP(baseMesh.positions[i])));
		}
		return VeinMesh(std::move(transfromedPositions), baseMesh.indices);
	}
}