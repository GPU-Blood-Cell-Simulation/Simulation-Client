#include "physics_config.hpp"

#include "../../defines.hpp"
#include "../exceptions.hpp"

#include <fstream>

namespace serializable
{
	void PhysicsConfig::serializeToCpp() const
	{
		std::ofstream os(physicsCppSerializationPath);
		if (!os)
			throw FileOpenException();

		os << "#pragma once\n#include \"simulation.hpp\"\n\n";
		os << "inline constexpr float velocity_collision_damping = " << velocity_collision_damping << ";\n";
		os << "inline constexpr float particle_k_sniff = " << particle_k_sniff << ";\n";
		os << "inline constexpr float vein_k_sniff = " << vein_k_sniff << ";\n\n";

		os << "inline constexpr float particle_d_fact = " << particle_d_fact << ";\n";
		os << "inline constexpr float vein_d_fact = " << vein_d_fact << ";\n\n";

		os << "inline constexpr float viscous_damping = " << viscous_damping << ";\n";
		os << "inline constexpr float vein_boundaries_velocity_damping = " << vein_boundaries_velocity_damping << ";\n";
		os << "inline constexpr float vein_collision_force_intensity = " << vein_collision_force_intensity << ";\n\n";

		os << "inline constexpr float collisionSpringCoeff = " << collisionSpringCoeff << ";\n";
		os << "inline constexpr float collisionDampingCoeff = " << collisionDampingCoeff << ";\n";
		os << "inline constexpr float collistionShearCoeff = " << collistionShearCoeff << ";\n\n";

		os << "inline constexpr float initVelocityX = " << initVelocity.x << ";\n";
		os << "inline constexpr float initVelocityY = " << initVelocity.y << ";\n";
		os << "inline constexpr float initVelocityZ = " << initVelocity.z << ";\n";
		os << "inline constexpr float randomVelocityModifier = " << randomVelocityModifier << ";\n\n";

		os << "inline constexpr float veinImpactDistance = " << veinImpactDistance << ";\n";
		os << "inline constexpr float veinImpactMinimalForceDistance = " << veinImpactMinimalForceDistance << ";\n\n";

		os << "inline constexpr float Gx = " << gravity.x << ";\n";
		os << "inline constexpr float Gy = " << gravity.y << ";\n";
		os << "inline constexpr float Gz = " << gravity.z << ";\n";

		if (!os)
			throw FileWriteException();
	}
}