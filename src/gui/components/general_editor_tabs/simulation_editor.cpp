#include "../../gui_controller.hpp"

#include "../../extensions.hpp"

namespace gui
{
	void GUIController::renderSimulationEditor()
	{
		auto& data = configManager.getData().generalConfig.simulation;

		ext::InputPositiveFloat("Simulation time (s)", &data.simulationTime);
		ext::InputPositiveFloat("Delta time (dt)", &data.dt, 0.001f);
		ImGui::Checkbox("Use blood flow", &data.useBloodFlow);
		ImGui::Checkbox("Enable reaction force", &data.enableReactionForce);
		ImGui::NewLine();

		ext::InputPositiveInt("Grid cell width", &data.cellWidth);
		ext::InputPositiveInt("Grid cell height)", &data.cellHeight);
		ext::InputPositiveInt("Grid cell depth", &data.cellDepth);
		ImGui::NewLine();

		ext::InputPositiveInt("Bounding sphere coefficient", &data.boundingSpheresCoeff);
		ext::InputPositiveFloat("Grid margin", &data.gridMargin);
		ImGui::InputFloat("Maximum particle spawn Y", &data.minSpawnY);
		if (data.minSpawnY > 0)
			data.minSpawnY = 0;
	}
}