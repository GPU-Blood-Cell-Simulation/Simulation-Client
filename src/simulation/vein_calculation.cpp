#include "vein_calculation.hpp"

#include "../defines.hpp"

namespace sim
{
	Mesh createVeinMesh(const serializable::VeinDefinition& veinDefinition)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		// TODO : read these from definitions
		const float radius = cylinderRadius;
		const float height = cylinderHeight;
		const int vLayers = cylinderVerticalLayers;
		const int hLayers = cylinderHorizontalLayers;
		glm::vec3 basisOrigin = cylinderBaseCenter;

		float triangleH = height / vLayers;
		float radianBatch = 2 * glm::pi<float>() / hLayers;
		float triangleBase = radianBatch * radius;
		for (unsigned int i = 0; i < vLayers; ++i)
		{
			float h = i * triangleH /*- height / 2*/;
			for (unsigned int j = 0; j < hLayers; ++j)
			{
				glm::vec3 position = glm::vec3(radius * cos(j * radianBatch),
					h, radius * sin(j * radianBatch)) + basisOrigin;
				Vertex v
				{
					position,
					glm::vec3(glm::normalize(position - glm::vec3(basisOrigin.x, basisOrigin.y, basisOrigin.z + h))),
					glm::vec2(0) // no textures
				};

				vertices.push_back(v);
				if (i < vLayers - 1)
				{
					int nextj = (j + 1) % hLayers;
					indices.push_back((i + 1) * hLayers + j);
					indices.push_back(i * hLayers + j);
					indices.push_back(i * hLayers + nextj);
					indices.push_back((i + 1) * hLayers + j);
					indices.push_back(i * hLayers + nextj);
					indices.push_back((i + 1) * hLayers + nextj);
				}
			}
		}

		return Mesh(std::move(vertices), std::move(indices),
			std::move(std::vector<Texture>(0)));
	}
}
