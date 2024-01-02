#pragma once

#include "../cpp_serializable.hpp"
#include "../util/nameof.hpp"

#include <nlohmann/json.hpp>

namespace serializable
{
	using json = nlohmann::json;

	struct PhysicsConfig : public ICppSerializable
	{
		// factor to slow down particles after collision
		float velocity_collision_damping = 0.96f;

		// ! this value should be determined experimentally !
		// Hooks law k factor from F = k*x
		float particle_k_sniff = 20.0f;
		float vein_k_sniff = 0.05f;

		// Damping factor. This value should be about sqrt(4*particle_k_sniff)
		float particle_d_fact = 9.0f;
		float vein_d_fact = 0.45f;

		// viscous damping slows down particle proportionally to its velocity
		float viscous_damping = 0.3f;

		// suppression coefficient to slow down particles on vein boundaries
		float vein_boundaries_velocity_damping = 0.65f;

		// scale factor to calculate force applied to vein on collision with particle
		float vein_collision_force_intensity = 0.08f;

		// Particle-particle collision coefficients
		float collisionSpringCoeff = 6.0f;
		float collisionDampingCoeff = 6.0f;
		float collistionShearCoeff = 4.0f;

		// Initial velocity of particlesvariant
		glm::vec3 initVelocity{ 0.0f, -80.0f, 0.0f };
		float randomVelocityModifier = 0.894f;


		// distance beetwen particle and vein on which an impact occurs
		float veinImpactDistance = 6.0f;
		float veinImpactMinimalForceDistance = 0.0001f;

		// gravity power
		glm::vec3 gravity{ 0.0f, -25.0f, 0.0f };

		virtual void serializeToCpp() const override {}
	};

	inline void to_json(json& j, const PhysicsConfig& o)
	{
		j = json{
			{nameof(o.velocity_collision_damping), o.velocity_collision_damping},
			{nameof(o.particle_k_sniff), o.particle_k_sniff},
			{nameof(o.vein_k_sniff), o.vein_k_sniff},
			{nameof(o.particle_d_fact), o.particle_d_fact},
			{nameof(o.vein_d_fact), o.vein_d_fact},
			{nameof(o.viscous_damping), o.viscous_damping},
			{nameof(o.vein_boundaries_velocity_damping), o.vein_boundaries_velocity_damping},
			{nameof(o.vein_collision_force_intensity), o.vein_collision_force_intensity},
			{nameof(o.collisionSpringCoeff), o.collisionSpringCoeff},
			{nameof(o.collisionDampingCoeff), o.collisionDampingCoeff},
			{nameof(o.collistionShearCoeff), o.collistionShearCoeff},
			{nameof(o.initVelocity), o.initVelocity},
			{nameof(o.randomVelocityModifier), o.randomVelocityModifier},
			{nameof(o.veinImpactDistance), o.veinImpactDistance},
			{nameof(o.veinImpactMinimalForceDistance), o.veinImpactMinimalForceDistance},
			{nameof(o.gravity), o.gravity}
		};
	}

	inline void from_json(const json& j, PhysicsConfig& o)
	{
		j.at(nameof(o.velocity_collision_damping)).get_to(o.velocity_collision_damping);
		j.at(nameof(o.particle_k_sniff)).get_to(o.particle_k_sniff);
		j.at(nameof(o.vein_k_sniff)).get_to(o.vein_k_sniff);
		j.at(nameof(o.particle_d_fact)).get_to(o.particle_d_fact);
		j.at(nameof(o.vein_d_fact)).get_to(o.vein_d_fact);
		j.at(nameof(o.viscous_damping)).get_to(o.viscous_damping);
		j.at(nameof(o.vein_boundaries_velocity_damping)).get_to(o.vein_boundaries_velocity_damping);
		j.at(nameof(o.vein_collision_force_intensity)).get_to(o.vein_collision_force_intensity);
		j.at(nameof(o.collisionSpringCoeff)).get_to(o.collisionSpringCoeff);
		j.at(nameof(o.collisionDampingCoeff)).get_to(o.collisionDampingCoeff);
		j.at(nameof(o.collistionShearCoeff)).get_to(o.collistionShearCoeff);
		j.at(nameof(o.initVelocity)).get_to(o.initVelocity);
		j.at(nameof(o.randomVelocityModifier)).get_to(o.randomVelocityModifier);
		j.at(nameof(o.veinImpactDistance)).get_to(o.veinImpactDistance);
		j.at(nameof(o.veinImpactMinimalForceDistance)).get_to(o.veinImpactMinimalForceDistance);
		j.at(nameof(o.gravity)).get_to(o.gravity);
	}
}