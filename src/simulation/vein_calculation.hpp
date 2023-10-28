#pragma once

#include "../graphics/models/mesh.hpp"
#include "../serializable/vein_definition.hpp"

namespace sim
{
	Mesh createVeinMesh(const serializable::VeinDefinition& veinDefinition);
}