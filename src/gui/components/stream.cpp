#include "../gui_controller.hpp"

#include "../extensions.hpp"


namespace gui
{
	void GUIController::renderStream()
	{
		
		
		switch (streamManager.streamStatusGet())
		{
		case streaming::StreamStatus::initStatus:
			ext::CenteredText("Stream initiates");
			break;

		case streaming::StreamStatus::waitingForServer:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,210,0,255)); // Yellow text
			ext::CenteredText("Connecting to server...");
			ImGui::PopStyleColor();
			break;

		case streaming::StreamStatus::inProgress:
			ext::CenteredText("Simulation in progress");
			break;

		case streaming::StreamStatus::successfullyEnded:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(25,200,25,255)); // Green text
			ext::CenteredText("Simulation successfully ended");
			ImGui::PopStyleColor();
			break;

		case streaming::StreamStatus::connectionLost:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(235, 64, 52,255)); // Red text
			ext::CenteredText("Connection with server lost!!!");
			ImGui::PopStyleColor();
			break;
		
		default:
			break;
		}

		ImGui::NewLine();
		if (ext::CenteredButton("Abort simulation"))
			streamManager.abortSimulation();

		
		ImGui::NewLine();
		if (ext::CenteredButton("Stop watching stream"))
		{
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}
