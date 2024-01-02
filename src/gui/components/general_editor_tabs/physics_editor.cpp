#include "../../gui_controller.hpp"

#include "../../extensions.hpp"


namespace gui
{
	void GUIController::renderPhysicsEditor()
	{
		auto& data = configManager.getData().generalConfig.physics;
		float windowWidth = ImGui::GetWindowSize().x;
		if (windowWidth > 300)
			ImGui::PushItemWidth(windowWidth - 300);

		ext::InputPositiveFloat("Collision velocity damping", &data.velocity_collision_damping);
		ImGui::NewLine();

		ImGui::Text("Spring physics");
		ext::InputPositiveFloat("Particle k sniff", &data.particle_k_sniff);
		ext::InputPositiveFloat("Vein k sniff", &data.vein_k_sniff);
		ext::InputPositiveFloat("Particle d fact", &data.particle_d_fact);
		ext::InputPositiveFloat("Vein d fact", &data.vein_d_fact);
		ImGui::NewLine();

		ext::InputPositiveFloat("Viscous damping", &data.viscous_damping);
		ext::InputPositiveFloat("Velocity damping on vein boundaries", &data.vein_boundaries_velocity_damping);
		ext::InputPositiveFloat("Vein collision force intensity", &data.vein_collision_force_intensity);
		ImGui::NewLine();

		ImGui::Text("Particle-particle collisions");
		ext::InputPositiveFloat("Particle collision spring coefficient", &data.collisionSpringCoeff);
		ext::InputPositiveFloat("Particle collision damping coefficient", &data.collisionDampingCoeff);
		ext::InputPositiveFloat("Particle collision shear coefficient", &data.collistionShearCoeff);
		ImGui::NewLine();

		ImGui::InputFloat3("Initial velocity (x, y, z)", (float*)(&data.initVelocity));
		ext::InputPositiveFloat("Random velocity modifier", &data.randomVelocityModifier);
		ImGui::NewLine();

		ImGui::Text("Vein collision detection");
		ext::InputPositiveFloat("Vein impact distance", &data.veinImpactDistance);
		ext::InputPositiveFloat("Vein impact minimum force distance", &data.veinImpactMinimalForceDistance);

		ImGui::NewLine();
		ImGui::InputFloat3("Gravity (x, y, z)", (float*)(&data.gravity));

	}
}