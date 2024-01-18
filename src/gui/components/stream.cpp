#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderStream()
	{
		ImGui::Text("Simulation in progress");

		if (ImGui::Button("Done"))
		{
			setMode(Mode::mainScreen);
			glController.endSimulation();
		}
	}
}
