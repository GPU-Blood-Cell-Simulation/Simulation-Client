#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		ImGui::Text("Simulation in progress");

		Imgui::T

		if (ImGui::Button("Abort simulation"))
			glController.abortSimulation();

		if (ImGui::Button("Stop watching stream"))
		{
			setMode(Mode::mainScreen);
			glController.endSimulation();
		}
	}
}