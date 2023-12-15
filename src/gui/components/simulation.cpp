#include "../gui_controller.hpp"

namespace gui
{
	void GUIController::renderSimulation()
	{
		ImGui::Text("Simulation in progress");
		streamReceiver.renderFrame();

		if (ImGui::Button("Done"))
		{
			streamReceiver.pause();
			
			setMode(Mode::mainScreen);
			glController.setMode(graphics::Mode::None);
		}
	}
}