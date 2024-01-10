#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		//ImGui::Text("Simulation in progress");

		if (ImGui::Button("Abort simulation"))
			streamManager.abortSimulation();

		switch (streamManager.streamStatusGet())
		{
		case streaming::StreamStatus::initStatus:
			ImGui::Text("Stream is getting ready");
			break;

		case streaming::StreamStatus::waitingForServer:
			ImGui::Text("Connecting to server...");
			break;

		case streaming::StreamStatus::inProgress:
			ImGui::Text("Simulation in progress");
			break;

		case streaming::StreamStatus::successfullyEnded:
			ImGui::Text("Simulation successfully ended");
			break;

		case streaming::StreamStatus::connectionLost:
			ImGui::Text("Connection with server lost!");
			break;
		
		default:
			break;
		}

		if (ImGui::Button("Stop watching stream"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}