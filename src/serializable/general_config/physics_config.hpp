#pragma once

#pragma once

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct PhysicsConfig
	{
		// Blood flow
		bool useBloodFlow = true;

		// factor to slow down particles after collision
		float velocityCollisionDamping = 0.8f;

		// Hooks law k factor from F = k*x
		float particle_k_sniff = 0.1f;
		float vein_k_sniff = 0.3f;

		// Damping factor 
		float particle_d_fact = 0.1f;
		float vein_d_fact = 0;

		// Particle-particle collision coefficients
		float collisionSpringCoeff = 0.2f;
		float collisionDampingCoeff = 0.02f;
		float collistionShearCoeff = 0.05f;

		// Initial velocity of particles
		float initVelocityX = 0.0f;
		float initVelocityY = -10.0f;
		float initVelocityZ = 0.0f;

		// distance beetwen particle and vein on which an impact occurs
		float veinImpactDistance = 5.0f;
	};

	inline void to_json(json& j, const PhysicsConfig& o)
	{
		// TODO
	}

	inline void from_json(const json& j, PhysicsConfig& o)
	{
		// TODO
	}
}