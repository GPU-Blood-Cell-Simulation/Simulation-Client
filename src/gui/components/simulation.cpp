#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		ImGui::Text("Simulation in progress");

		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.endSimulation();
		}
	}
}