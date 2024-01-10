#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		ImGui::Text("Simulation in progress");

		if (ImGui::Button("Abort simulation"))
			glController.abortSimulation();

		switch (glController.simulationStatusGet())
		{
		case graphics::SimulationStatus::waitingForServer:
			ImGui::Text("Connecting to server...");
			break;

		case graphics::SimulationStatus::inProgress:
			ImGui::Text("Simulation in progress");
			break;

		case graphics::SimulationStatus::successfullyEnded:
			ImGui::Text("Simulation successfully ended");
			break;

		case graphics::SimulationStatus::connectionLost:
			ImGui::Text("Connection with server lost!");
			break;
		
		default:
			break;
		}

		if (ImGui::Button("Stop watching stream"))
		{
			setMode(Mode::mainScreen);
			glController.endSimulation();
		}
	}
}